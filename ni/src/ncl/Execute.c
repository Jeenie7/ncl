

/*
 *      $Id: Execute.c,v 1.2 1993-12-30 00:44:21 ethan Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1993			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		Execute.c
 *
 *	Author:		Ethan Alpert
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Thu Oct 14 12:35:16 MDT 1993
 *
 *	Description:	
 */
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <ncarg/hlu/hlu.h>
#include <data_objs/NclVar.h>
#include <data_objs/NclMultiDValdoubleData.h>
#include <data_objs/NclMultiDValfloatData.h>
#include <data_objs/NclMultiDValintData.h>
#include <data_objs/NclMultiDValshortData.h>
#include <data_objs/NclMultiDVallongData.h>
#include <data_objs/NclMultiDValstringData.h>
#include <defs.h>
#include <Symbol.h>
#include <errno.h>
#include <OpsList.h>
#include <Machine.h>
#include <Execute.h>
#include <OpsFuncs.h>
#include <y.tab.h>
#include <data_objs/DataSupport.h>

extern int cmd_line;


NclExecuteReturnStatus _NclExecute
#if __STDC__
(unsigned long start_offset)
#else 
(start_offset) 
	unsigned long start_offset;
#endif
{
	NclValue *ptr;
	int *lptr;
	char **fptr;
	NclValue *machine;
	NhlErrorTypes status = NOERROR;

	machine = _NclGetCurrentMachine();
	ptr = machine + start_offset;
	lptr = _NclGetCurrentLineRec() + start_offset;
	fptr = _NclGetCurrentFileNameRec() + start_offset;

	while(1) {
		switch(*ptr) {
/****************************
* Zero Operand Instructions *
****************************/
			case STOPSEQ:
				return(Ncl_STOPS);
			case CONTINUE_OP:
				return(Ncl_CONTINUES);
			case BREAK_OP:
				return(Ncl_BREAKS);
			case ENDSTMNT_OP:
			case NOOP :
				break;
			case NAMED_INT_SUBSCRIPT_OP :
				break;
			case INT_SUBSCRIPT_OP : {
				NclStackEntry data;
				NclStackEntry data1;
				int mask = (int)(Ncl_MultiDVallongData | Ncl_MultiDValintData | Ncl_MultiDValshortData); 

/*
* This is the first place that type checks on the vectors and range values can
* be done since it isn't until here that it is determined that normal integer
* subscripting is going on
*/
				data = _NclPop();
	
				data1.kind = NclStk_SUBREC;
				data1.u.sub_rec = (NclSubRec*)NclMalloc(
					sizeof(NclSubRec));
				if(data.kind == NclStk_VECREC) {
					if(data.u.vec_rec->vec->obj.obj_type_mask & mask ) {
						data1.u.sub_rec->sub_type = INT_VECT;
						data1.u.sub_rec->u.vec = data.u.vec_rec;
					} else{
						NhlPError(FATAL,E_UNKNOWN,"Illegal subscript. Vector subscripts must be integer");
						status = FATAL;
					}
				} else if(data.kind == NclStk_RANGEREC) {
					if(((data.u.range_rec->start == NULL)
						|| (data.u.range_rec->start->obj.obj_type_mask & mask)) &&
					((data.u.range_rec->finish == NULL)
						||(data.u.range_rec->finish->obj.obj_type_mask & mask)) &&
					((data.u.range_rec->stride == NULL)
						||(data.u.range_rec->stride->obj.obj_type_mask & mask))) {
						data1.u.sub_rec->sub_type = INT_RANGE;
						data1.u.sub_rec->u.range = data.u.range_rec;
					} else {
						NhlPError(FATAL,E_UNKNOWN,"Illegal subscript. Subscripts must be integer when not using coordinate indexing");
						status = FATAL;
					}
				}
				if(*ptr == INT_SUBSCRIPT_OP) {
					data1.u.sub_rec->name = NULL;
				} else {
					data = _NclPop();
					switch(data.kind) {
					case NclStk_VAL: {
/*
* Taking for granted that syntax only allows string litterals here
*/
						data1.u.sub_rec->name = NclMalloc(strlen((char*) data.u.data_obj->multidval.val));
						strcpy(data1.u.sub_rec->name,data.u.data_obj->multidval.val);			
						_NclDestroyObj((NclObj)data.u.data_obj);
						
						break;
					}
					default:	
						NhlPError(WARNING,E_UNKNOWN,"Illegal type for coordinate name in coordinate subscript ignoring value");
						data1.u.sub_rec->name = NULL;
						break;
					}
				}
				_NclPush(data1);
				break;
			}
			case DEFAULT_RANGE_OP : {
				NclStackEntry data;
				data.kind = NclStk_NOVAL;
				data.u.offset = 0;
				_NclPush(data);
				break;
			}
			case RANGE_INDEX_OP : {
				NclStackEntry start;
				NclStackEntry finish;
				NclStackEntry stride;
				NclStackEntry data;

				stride = _NclPop();
				finish = _NclPop();
				start  = _NclPop();
				data.kind = NclStk_RANGEREC;
				data.u.range_rec = (NclRangeRec*)NclMalloc(
					sizeof(NclRangeRec));
				if(start.kind == NclStk_NOVAL) {
					data.u.range_rec->start = NULL;
				} else {
					switch(start.kind) {
					case NclStk_VAL:
						if(start.u.data_obj !=NULL) {
						data.u.range_rec->start = start.u.data_obj;
						} else {
							status = FATAL;
						}
						break;
					case NclStk_VAR:
						data.u.range_rec->start = 
								_NclGetVarVal(start.u.data_var);
						if(data.u.range_rec->start == NULL) {
							status = FATAL;
						}
						break;
					default:
						status = FATAL;
						break;
					}
				}
				if(finish.kind == NclStk_NOVAL) {
					data.u.range_rec->finish = NULL;
				} else {
					switch(finish.kind) {
					case NclStk_VAL:
						if(finish.u.data_obj !=NULL) {
						data.u.range_rec->finish= finish.u.data_obj;
						} else {
							status = FATAL;
						}
						break;
					case NclStk_VAR:
						data.u.range_rec->finish= _NclGetVarVal(finish.u.data_var);
						if(data.u.range_rec->finish == NULL) {
							status = FATAL;
						}
						break;
					default:
						status = FATAL;
						break;
					}
				}
				if(stride.kind == NclStk_NOVAL) {
					data.u.range_rec->stride= NULL;
				} else {
					switch(stride.kind) {
					case NclStk_VAL:
						if(stride.u.data_obj !=NULL) {
						data.u.range_rec->stride= stride.u.data_obj;
						} else {
							status = FATAL;
						}
						break;
					case NclStk_VAR:
						data.u.range_rec->stride= _NclGetVarVal(stride.u.data_var);
						if(data.u.range_rec->stride == NULL){
							status = FATAL;
						}
						break;
					default:
						status = FATAL;
						break;
					}
				}
				if((data.u.range_rec->start != NULL) &&
					(data.u.range_rec->start->multidval.kind != SCALAR)) {
					NhlPError(FATAL,E_UNKNOWN,"Illegal Subscript. Only scalar values are allowed in subscript ranges.\n");
					status = FATAL;
				}
				if((data.u.range_rec->finish != NULL) &&
					(data.u.range_rec->finish->multidval.kind != SCALAR)) {
					NhlPError(FATAL,E_UNKNOWN,"Illegal Subscript. Only scalar values are allowed in subscript ranges.\n");
					status = FATAL;
				}
				if((data.u.range_rec->stride != NULL) &&
					(data.u.range_rec->stride->multidval.kind != SCALAR)) {
					NhlPError(FATAL,E_UNKNOWN,"Illegal Subscript. Only scalar values are allowed in subscript ranges.\n");
					status = FATAL;
				}
				_NclPush(data);
				break;
			}
			case SINGLE_INDEX_OP : {
				NclStackEntry data;
				NclStackEntry data1;
				NclMultiDValData val;

				data = _NclPop();
				switch(data.kind) {
				case NclStk_VAR: 
					val = _NclGetVarVal(data.u.data_var);;
					if(val == NULL){
						status = FATAL;
					}
					break;
				case NclStk_VAL:
					if(data.u.data_obj != NULL) {
						val = data.u.data_obj;
					} else {
						status = FATAL;
					}
					break;
				default:
					status = FATAL;
				}
				if(status != FATAL) {
					if(val->multidval.kind == SCALAR) {
						data1.kind = NclStk_RANGEREC;
						data1.u.range_rec = 
							(NclRangeRec*)NclMalloc(
							sizeof(NclRangeRec));
						data1.u.range_rec->start = val;
						data1.u.range_rec->finish = val;
						data1.u.range_rec->stride=NULL;
						_NclPush(data1);
					} else if(val->multidval.n_dims == 1) {
						data1.kind = NclStk_VECREC;
						data1.u.vec_rec =
							(NclVecRec*)NclMalloc(
							sizeof(NclVecRec));
						data1.u.vec_rec->vec = val;
						_NclPush(data1);
					} else {
						NhlPError(FATAL,E_UNKNOWN,"Illegal subscript. Subscripts must be scalar or one dimensional vectors\n");
						status = FATAL;
					}
				}
				break;
			}
			case RETURN_OP :
				break;
			case IF_OP :
				break;
			case NAMED_COORD_SUBSCRIPT_OP : 
				break;
			case COORD_SUBSCRIPT_OP : {
				NclStackEntry data;
				NclStackEntry data1;
				int mask = (int)(Ncl_MultiDVallongData | Ncl_MultiDValintData | Ncl_MultiDValshortData); 

/*
* This is the first place that type checks on the vectors and range values can
* be done since it isn't until here that it is determined that normal integer
* subscripting is going on
*/
				data = _NclPop();
	
				data1.kind = NclStk_SUBREC;
				data1.u.sub_rec = (NclSubRec*)NclMalloc(
					sizeof(NclSubRec));
				if(data.kind == NclStk_VECREC) {
					data1.u.sub_rec->sub_type = COORD_VECT;
					data1.u.sub_rec->u.vec = data.u.vec_rec;
				} else if(data.kind == NclStk_RANGEREC) {
					if(((data.u.range_rec->stride == NULL)
						||(data.u.range_rec->stride->obj.obj_type_mask & mask))) {
						data1.u.sub_rec->sub_type = COORD_RANGE;
						data1.u.sub_rec->u.range = data.u.range_rec;
					} else {
						NhlPError(FATAL,E_UNKNOWN,"Illegal subscript. stride must always be integer regardless of whether coordinate or integer subscripting is being used\n");
						status = FATAL;
					}
				}
				if(*ptr == COORD_SUBSCRIPT_OP) {
					data1.u.sub_rec->name = NULL;
				} else {
					data = _NclPop();
					switch(data.kind) {
					case NclStk_VAL: {
/*
* Taking for granted that syntax only allows string litterals here
*/
						data1.u.sub_rec->name = NclMalloc(strlen((char*) data.u.data_obj->multidval.val));
						strcpy(data1.u.sub_rec->name,data.u.data_obj->multidval.val);			
						_NclDestroyObj((NclObj)data.u.data_obj);
						
						break;
					}
					default:	
						NhlPError(WARNING,E_UNKNOWN,"Illegal type for coordinate name in coordinate subscript ignoring value");
						data1.u.sub_rec->name = NULL;
						break;
					}
				}
				_NclPush(data1);
				break;
			} 
			case NEG_OP : {
				NclStackEntry data;
				NclStackEntry operand;
				operand = _NclPop();
				status = _NclMonoOp(operand,&data,NEG_OP);
				_NclPush(data);
			}
			break;
			case NOT_OP : {
				NclStackEntry data;
				NclStackEntry operand;
				operand = _NclPop();
				status = _NclMonoOp(operand,&data,NOT_OP);
				_NclPush(data);
			}
			break;
			case MOD_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,MOD_OP);
				_NclPush(data);
			}
			break;
			case OR_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,OR_OP);
				_NclPush(data);
			}
			break;
			case AND_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,AND_OP);
				_NclPush(data);
			}
			break;
			case XOR_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,XOR_OP);
				_NclPush(data);
			}
			break;
			case LTSEL_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,LTSEL_OP);
				_NclPush(data);
			}
			break;
			case GTSEL_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,GTSEL_OP);
				_NclPush(data);
			}
			break;
			case PLUS_OP :
			{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status =  _NclDualOp(lhs,rhs,&data,PLUS_OP);
				_NclPush(data);
			}
				break;
			case MINUS_OP :
			{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,MINUS_OP);
				_NclPush(data);
			}
				break;
			case MUL_OP :
			{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,MUL_OP);
				_NclPush(data);
			}
				break;
			case MAT_OP :
			{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,MAT_OP);
				_NclPush(data);
			}
				break;
			case DIV_OP :
			{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,DIV_OP);
				_NclPush(data);
			}
				break;
			case EXP_OP :{
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,EXP_OP);
				_NclPush(data);
			}
			break;
			case LE_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,LE_OP);
				_NclPush(data);
			}
			break;
			case GE_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,GE_OP);
				_NclPush(data);
			}
			break;
			case GT_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,GT_OP);
				_NclPush(data);
			}
			break;
			case LT_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,LT_OP);
				_NclPush(data);
			}
			break;
			case EQ_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,EQ_OP);
				_NclPush(data);
			}
			break;
			case NE_OP : {
				NclStackEntry data;
				NclStackEntry lhs;
				NclStackEntry rhs;
				lhs = _NclPop();
				rhs = _NclPop();
				status = _NclDualOp(lhs,rhs,&data,NE_OP);
				_NclPush(data);
			}
			break;
/***************************
* One Operand Instructions *
***************************/
			case FPDEF:
				ptr++;lptr++;fptr++;
				break;
			case JMP:
			{
				ptr++;lptr++;fptr++;
/*
* Needs to be substracted by one so ptr++ is valid
*/
				ptr = machine + (*ptr - 1);		
				break;
			}
			case ARRAY_LIT_OP :
			{
				NclStackEntry data;
				ptr++;lptr++;fptr++;
				status = _NclBuildArray((int)*ptr,&data);
				_NclPush(data);
				break;
			}
			case PUSH_STRING_LIT_OP :
			{
				NclStackEntry data;
				char **thestr;
				int dim_size = 1;
			
				ptr++;lptr++;fptr++;
				data.kind = NclStk_VAL;
				thestr = (char**)NclMalloc((unsigned)sizeof(char*));
				*thestr = (char*)NclMalloc((unsigned)strlen((char*)*ptr + 1));
				strcpy(*thestr,(char*)ptr);
				data.u.data_obj = _NclMultiDValstringCreate(NULL,
						(void*)thestr,NULL,1,&dim_size,
						NULL,TEMPORARY,NULL);
				_NclPush(data);
				break;
			}
			case PUSH_REAL_LIT_OP : 
			{
				NclStackEntry data;
				int dim_size = 1;
				ptr++;lptr++;fptr++;
				data.kind = NclStk_VAL;
				data.u.data_obj = _NclMultiDValfloatCreate(NULL,
						(void*)ptr,NULL,1,&dim_size,
						NULL,STATIC,NULL);
				_NclPush(data);
				break;
			}
			case PUSH_INT_LIT_OP :
			{
				NclStackEntry data;
				int dim_size = 1;
				ptr++;lptr++;fptr++;
				data.kind = NclStk_VAL;
				data.u.data_obj = _NclMultiDValintCreate(NULL,
						(void*)ptr,NULL,1,&dim_size,
						NULL,STATIC,NULL);
				_NclPush(data);
				break;
			}
			case JMPFALSE :
				ptr++;lptr++;fptr++;
				break;
			case CREATE_OBJ_OP :
				ptr++;lptr++;fptr++;
				break;
			case SET_OBJ_OP :
				ptr++;lptr++;fptr++;
				break;
			case GET_OBJ_OP :
				ptr++;lptr++;fptr++;
				break;
			case PROC_CALL_OP:
				ptr++;lptr++;fptr++;
				break;
			case BPROC_CALL_OP:
			{
				int i;
				ptr++;lptr++;fptr++;
/*
* This is not going to work because nothing is done to unpack the
* arguments they are just popped now!!!!!!
*/
				if(((NclSymbol*)*ptr)->u.bproc != NULL) {
					(*((NclSymbol*)*ptr)->u.bproc->theproc)();
					for(i = 0;i<((NclSymbol*)*ptr)->u.bproc->nargs; i++) {
						(void)_NclPop();
					}
				}
			}
				break;
			case FUNC_CALL_OP:
				ptr++;lptr++;fptr++;
				break;
			case BFUNC_CALL_OP:
				ptr++;lptr++;fptr++;
				break;
			case DO_FROM_TO_OP :
				ptr++;lptr++;fptr++;
				break;
			case DO_FROM_TO_STRIDE_OP :
				ptr++;lptr++;fptr++;
				break;
/***************************
* Two Operand Instructions *
***************************/			
			case VAR_DIMNUM_OP:
			case ASSIGN_VAR_DIMNUM_OP:
			case PARAM_VAR_DIMNUM_OP:
			case VAR_DIMNAME_OP:
			case ASSIGN_VAR_DIMNAME_OP:
			case PARAM_VAR_DIMNAME_OP:
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				break;
			case PARAM_VAR_OP:
			case VAR_OP : {
				int i;
				int nsubs;
				NclStackEntry data;
				NclStackEntry data1;
				NclStackEntry* var;
				NclSymbol *sym;
				NclSelectionRecord *sel_ptr=NULL;

				ptr++;lptr++;fptr++;
				sym = (NclSymbol*)*ptr;
				var = _NclRetrieveRec(sym);
				ptr++;lptr++;fptr++;
				nsubs = *ptr;
				if(nsubs == 0) {
					if(var != NULL) {
						_NclPush(*var);
					}
				} else {
					sel_ptr = (NclSelectionRecord*)NclMalloc
						(sizeof(NclSelectionRecord));
					sel_ptr->n_entries = nsubs;
					for(i=0;i<nsubs;i++) {
						data =_NclPop();
						switch(data.u.sub_rec->sub_type) {
						case INT_VECT:
/*
* Need to free some stuff here
*/							
							_NclBuildVSelection(var->u.data_var,data.u.sub_rec->u.vec,&(sel_ptr->selection[i]),i,data.u.sub_rec->name);
							break;
						case INT_RANGE:
/*
* Need to free some stuff here
*/							
							_NclBuildRSelection(var->u.data_var,data.u.sub_rec->u.range,&(sel_ptr->selection[i]),i,data.u.sub_rec->name);
							break;
						case COORD_VECT:
						case COORD_RANGE:
							break;
						}
					}
					data1.kind = NclStk_VAL;
					data1.u.data_obj = _NclVarValueRead(var->u.data_var,sel_ptr);
					_NclPush(data1);
				}
				break;
			}
			case ASSIGN_VAR_OP :{
				NclStackEntry rhs;
				NclStackEntry data;
				NclStackEntry *lhs_var;
				NclMultiDValData rhs_md;
				int i,nsubs;	
				NclSymbol *sym;
			
			rhs = _NclPop();	
			if(rhs.kind == NclStk_VAL) {
				rhs_md = rhs.u.data_obj;
			} else if(rhs.kind == NclStk_VAR) {
				rhs_md = _NclGetVarVal(rhs.u.data_var);
			} else {
				NhlPError(FATAL,E_UNKNOWN,"Illegal right-hand side type for assignment");
				status = FATAL;
			}

			ptr++;lptr++;fptr++;
			sym = (NclSymbol*)(*ptr);

			ptr++;lptr++;fptr++;
			nsubs = 0;

			lhs_var = _NclRetrieveRec(sym);
			if((status != FATAL)&&(lhs_var != NULL)) {
				if(lhs_var->kind == NclStk_NOVAL) {
					if(nsubs != 0) {
						status = FATAL;
						NhlPError(FATAL,E_UNKNOWN,"Assign: %s is undefined, can not subscript an undefined variable",sym->name);
						status = FATAL;
						for(i=0;i<nsubs;i++) {
/*
* Need to free this stuff
*/
							(void)_NclPop();
						}
					} else {
						lhs_var->u.data_var= _NclVarCreate(sym,rhs_md);
						if(lhs_var->u.data_var != NULL) {
							(void)_NclChangeSymbolType(sym,VAR);
							lhs_var->kind = NclStk_VAR;
							
						} else {
							NhlPError(WARNING,E_UNKNOWN,"Could not create variable (%s)",sym->name);
							status = WARNING;
							lhs_var->kind = NclStk_NOVAL;
						}
					}
				} else if(lhs_var->kind == NclStk_VAR) {
					if(nsubs != lhs_var->u.data_var->var.n_dims) {
						NhlPError(FATAL,E_UNKNOWN,"Number of subscripts (%d) and number of dimensions (%d) do not match for variable (%s)",nsubs,lhs_var->u.data_var->var.n_dims,sym->name);
						status = FATAL;
						for(i=0;i<nsubs;i++) {
/*
* Need to free this stuff
*/
							(void)_NclPop();
						}
					}
					for(i=0;i<nsubs;i++) {
/*
* code for building selection record
*/
						data =_NclPop();
					}
				} else {
					NhlPError(FATAL,E_UNKNOWN,"Assignment not supported for left-hand type");
					status = FATAL;
				}

			} else {
				for(i=0;i<nsubs;i++) {
/*
* code for building selection record
*/
					data =_NclPop();
				}
			}
			break;
			}
			case NEW_FRAME_OP:
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				break;
			case CONVERT_TO_LOCAL:
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				break;
			case DO_WHILE_OP :
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				break;
/*****************************
* Three Operand Instructions *
*****************************/
			case PARAM_FILE_VAR_OP:
			case PARAM_VARATT_OP:
			case PARAM_VAR_COORD_OP:
			case VAR_COORD_OP:
			case ASSIGN_VAR_COORD_OP:
			case VARATT_OP:
			case ASSIGN_VARATT_OP:
			case FILE_VAR_OP :
			case ASSIGN_FILE_VAR_OP :
			case FILEVAR_DIMNAME_OP:	
			case ASSIGN_FILEVAR_DIMNAME_OP:
			case PARAM_FILEVAR_DIMNAME_OP:
			case FILEVAR_DIMNUM_OP:	
			case ASSIGN_FILEVAR_DIMNUM_OP:
			case PARAM_FILEVAR_DIMNUM_OP:
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				break;
/*****************************
* Four Operand Instructions  *
*****************************/
			case FILEVARATT_OP:
			case ASSIGN_FILEVARATT_OP:
			case PARAM_FILEVARATT_OP:
			case FILEVAR_COORD_OP:
			case ASSIGN_FILEVAR_COORD_OP:
			case PARAM_FILEVAR_COORD_OP:
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
				ptr++;lptr++;fptr++;
			default:
				break;
		}

		if(status < INFO) {
			if(*fptr == NULL) {
				NhlPError(status,E_UNKNOWN,"Execute: Error occured at or near line %d\n",(cmd_line ? (*lptr)-1: *lptr));
			} else {
				NhlPError(status,E_UNKNOWN,"Execute: Error occured at or near line %d in file %s\n", *lptr, *fptr);
			}
			if(status < WARNING) {
/*
* need to clean up stack !!! for current level
*/
				return(Ncl_ERRORS);
			}
		}	
		status = NOERROR;	
		ptr++;lptr++;fptr++;
	}
}

#ifdef __cplusplus
}
#endif

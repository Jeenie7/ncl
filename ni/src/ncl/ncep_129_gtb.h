/* 
 * US National Weather Service - NCEP (WMC)
 * Center: 7
 * Subcenter: 0 
 * Parameter table version: 129
 */
 
TBLE2 ncep_129_params[] = {
{1, "Pressure", "Pa", "PRES"},
{2, "Pressure reduced to MSL", "Pa", "PRMSL"},
{3, "Pressure tendency", "Pa/s", "PTEND"},
{4, "Potential vorticity", "km^2/kg/s", "PVORT"},
{5, "ICAO Standard Atmosphere Reference Height", "M", "ICAHT"},
{6, "Geopotential", "m^2/s^2", "GP"},
{7, "Geopotential height", "gpm", "HGT"},
{8, "Geometric height", "m", "DIST"},
{9, "Std dev of height", "m", "HSTDV"},
{10, "Total ozone", "Dobson", "TOZONE"},
{11, "Temperature", "K", "TMP"},
{12, "Virtual temperature", "K", "VTMP"},
{13, "Potential temperature", "K", "POT"},
{14, "Pseudo-adiabatic potential temperature", "K", "EPOT"},
{15, "Maximum temperature", "K", "T_MAX"},
{16, "Minimum temperature", "K", "T_MIN"},
{17, "Dew point temperature", "K", "DPT"},
{18, "Dew point depression", "K", "DEPR"},
{19, "Lapse rate", "K/m", "LAPR"},
{20, "Visibility", "m", "VIS"},
{21, "Radar spectra (1)", "non-dim", "RDSP1"},
{22, "Radar spectra (2)", "non-dim", "RDSP2"},
{23, "Radar spectra (3)", "non-dim", "RDSP3"},
{24, "Parcel lifted index (to 500 hPa)", "K", "PLI"},
{25, "Temperature anomaly", "K", "TMP_A"},
{26, "Pressure anomaly", "Pa", "PRESA"},
{27, "Geopotential height anomaly", "gpm", "GPA"},
{28, "Wave spectra (1)", "non-dim", "WVSP1"},
{29, "Wave spectra (2)", "non-dim", "WVSP2"},
{30, "Wave spectra (3)", "non-dim", "WVSP3"},
{31, "Wind direction", "deg", "WDIR"},
{32, "Wind speed", "m/s", "WIND"},
{33, "u-component of wind", "m/s", "U_GRD"},
{34, "v-component of wind", "m/s", "V_GRD"},
{35, "Stream function", "m^2/s", "STRM"},
{36, "Velocity potential", "m^2/s", "V_POT"},
{37, "Montgomery stream function", "m^2/s^2", "MNTSF"},
{38, "Sigma coord. vertical velocity", "/s", "SGCVV"},
{39, "Pressure vertical velocity", "Pa/s", "V_VEL"},
{40, "Geometric vertical velocity", "m/s", "DZDT"},
{41, "Absolute vorticity", "/s", "ABS_V"},
{42, "Absolute divergence", "/s", "ABS_D"},
{43, "Relative vorticity", "/s", "REL_V"},
{44, "Relative divergence", "/s", "REL_D"},
{45, "Vertical u-component shear", "/s", "VUCSH"},
{46, "Vertical v-component shear", "/s", "VVCSH"},
{47, "Direction of current", "deg", "DIR_C"},
{48, "Speed of current", "m/s", "SP_C"},
{49, "u-component of current", "m/s", "UOGRD"},
{50, "v-component of current", "m/s", "VOGRD"},
{51, "Specific humidity", "kg/kg", "SPF_H"},
{52, "Relative humidity", "%", "R_H"},
{53, "Humidity mixing ratio", "kg/kg", "MIXR"},
{54, "Precipitable water", "kg/m^2", "P_WAT"},
{55, "Vapor pressure", "Pa", "VAPP"},
{56, "Saturation deficit", "Pa", "SAT_D"},
{57, "Evaporation", "kg/m^2", "EVP"},
{58, "Cloud Ice", "kg/m^2", "C_ICE"},
{59, "Precipitation rate", "kg/m^2/s", "PRATE"},
{60, "Thunderstorm probability", "%", "TSTM"},
{61, "Total precipitation", "kg/m^2", "A_PCP"},
{62, "Large scale precipitation", "kg/m^2", "NCPCP"},
{63, "Convective precipitation", "kg/m^2", "ACPCP"},
{64, "Snowfall rate water equivalent.", "kg/m^2/s", "SRWEQ"},
{65, "Water equivalent of accum. snow depth", "kg/m^2", "WEASD"},
{66, "Snow depth", "m", "SNO_D"},
{67, "Mixed layer depth", "m", "MIXHT"},
{68, "Transient thermocline depth", "m", "TTHDP"},
{69, "Main thermocline depth", "m", "MTHD"},
{70, "Main thermocline anomaly", "m", "MTH_A"},
{71, "Total cloud cover", "%", "T_CDC"},
{72, "Convective cloud cover", "%", "CDCON"},
{73, "Low level cloud cover", "%", "L_CDC"},
{74, "Mid level cloud cover", "%", "M_CDC"},
{75, "High level cloud cover", "%", "H_CDC"},
{76, "Cloud water", "kg/m^2", "C_WAT"},
{77, "Best lifted index (to 500 hPa)", "K", "BLI"},
{78, "Convective snow", "kg/m^2", "SNO_C"},
{79, "Large scale snow", "kg/m^2", "SNO_L"},
{80, "Water temperature", "K", "WTMP"},
{81, "Land-sea mask (land=1;sea=0)", "fraction", "LAND"},
{82, "Deviation of sea level from mean", "m", "DSL_M"},
{83, "Surface roughness", "m", "SFC_R"},
{84, "Albedo", "%", "ALBDO"},
{85, "Soil temperature", "K", "TSOIL"},
{86, "Soil moisture content", "kg/m^2", "SOIL_M"},
{87, "Vegetation", "%", "VEG"},
{88, "Salinity", "kg/kg", "SALTY"},
{89, "Density", "kg/m^3", "DEN"},
{90, "Water runoff", "kg/m^2", "WATR"},
{91, "Ice concentration (ice=1;no ice=0)", "fraction", "ICE_C"},
{92, "Ice thickness", "m", "ICETK"},
{93, "Direction of ice drift", "deg", "DICED"},
{94, "Speed of ice drift", "m/s", "SICED"},
{95, "u-component of ice drift", "m/s", "U_ICE"},
{96, "v-component of ice drift", "m/s", "V_ICE"},
{97, "Ice growth rate", "m/s", "ICE_G"},
{98, "Ice divergence", "/s", "ICE_D"},
{99, "Snow melt", "kg/m^2", "SNO_M"},
{100, "Sig height of wind waves and swell", "m", "HTSGW"},
{101, "Direction of wind waves", "deg", "WVDIR"},
{102, "Significant height of wind waves", "m", "WVHGT"},
{103, "Mean period of wind waves", "s", "WVPER"},
{104, "Direction of swell waves", "deg", "SWDIR"},
{105, "Significant height of swell waves", "m", "SWELL"},
{106, "Mean period of swell waves", "s", "SWPER"},
{107, "Primary wave direction", "deg", "DIRPW"},
{108, "Primary wave mean period", "s", "PERPW"},
{109, "Secondary wave direction", "deg", "DIRSW"},
{110, "Secondary wave mean period", "s", "PERSW"},
{111, "Net short wave radiation (surface)", "W/m^2", "NSWRS"},
{112, "Net long wave radiation(surface)", "W/m^2", "NLWRS"},
{113, "Net short wave radiation (top)", "W/m^2", "NSWRT"},
{114, "Net long wave radiation (top)", "W/m^2", "NLWRT"},
{115, "Long wave radiation", "W/m^2", "LWAVR"},
{116, "Short wave radiation", "W/m^2", "SWAVR"},
{117, "Global radiation", "W/m^2", "G_RAD"},
{118, "Brightness temperature", "K", "BRTMP"},
{119, "Radiance with respect to wave no.", "W/m/sr", "LWRAD"},
{120, "Radiance with respect ot wave len.", "W/m^3/sr", "SWRAD"},
{121, "Latent heat flux", "W/m^2", "LHTFL"},
{122, "Sensible heat flux", "W/m^2", "SHTFL"},
{123, "Boundary layer dissipation", "W/m^2", "BLYDP"},
{124, "Momentum flux, u component", "N/m^2", "U_FLX"},
{125, "Momentum flux, v component", "N/m^2", "V_FLX"},
{126, "Wind mixing energy", "J", "WMIXE"},
{127, "Image data", "none", "IMG_D"},
{128, "Probability anomaly of temp", "%", "PAOT"},
{129, "Probability anomaly of precip", "%", "PAOP"},
{131, "Rain fraction of total liquid water", "none", "FRAIN"},
{132, "Ice fraction of total condensate", "none", "FICE"},
{133, "Rime factor", "none", "FRIME"},
{134, "Convective cloud efficiency", "none", "CUEFI"},
{135, "Total condensate", "kg/kg", "TCOND"},
{136, "Total column-integrated cloud water", "kg/m^2", "TCOLW"},
{137, "Total column-integrated cloud ice", "kg/m^2", "TCOLI"},
{138, "Total column-integrated rain", "kg/m^2", "TCOLR"},
{139, "Total column-integrated snow", "kg/m^2", "TCOLS"},
{140, "Total column-integrated condensate", "kg/m^2", "TCOLC"},
{141, "Pressure of level from which parcel was lifted",	"Pa", "PLPL"},
{142, "Height of level from which parcel was lifted", "m", "HLPL"},
{170, "Ellrod Index", "non-dim", "ELRDI"},
{171, "Seconds prior to initial reference time", "sec", "TSEC"},
{180, "Ozone concentration", "PPB", "OZCON"},
{181, "Categorical ozone concentration", "non-dim", "OZCAT"}
};

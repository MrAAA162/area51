//==============================================================================
//  
//  x_flare.hpp
//  
//==============================================================================

#ifndef X_FLARE_HPP
#define X_FLARE_HPP

//==============================================================================
//  DEFINITIONS
//==============================================================================

#define FLARE_NAME_LENGTH   32

//==============================================================================
//  INCLUDES
//==============================================================================

#ifndef X_TYPES_HPP
#include "x_types.hpp"
#endif X_TYPES_HPP

//==============================================================================
//  TYPES
//==============================================================================

typedef void flare_fn( u32 Data1, u32 Data2 );

//==============================================================================
//  FUNCTIONS
//==============================================================================

void    flare_Hook  ( const char* pName, flare_fn* pFlareFn, 
                                         u32       Data1 = 0, 
                                         u32       Data2 = 0 );

void    flare_Fire  ( const char* pName );

//==============================================================================
#endif // X_FLARE_HPP
//==============================================================================


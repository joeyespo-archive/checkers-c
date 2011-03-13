// eSkinCore.h
// eSkin Core Header File
// By Joe Esposito


#pragma once



// Local Library Information
// ============================================================================
// 

// Library Macros
// ---------------

#define ESKIN_



// Library Structs
// ----------------

typedef struct _SKIN
{
  DWORD dwFlags;
} SKIN, *LPSKIN;

// 
// ============================================================================






// Create Skin Struct Flags
// -------------------------

// Skin types
#define CREATESKIN_NORMAL         0x00000000L       // Create normal skin [Valid Members: ].
#define CREATESKIN_ANIMATE        0x00000001L       // Create animation skin [Valid Members: ].
#define CREATESKIN_RAW            0x00000002L       // Send raw skin data [Valid Members: lpRawSkin].



// Create Skin Struct Flags
// -------------------------

// Raw skin types
#define RAWSKIN_REGIONED          0x00000001L       // Raw skin is a regioned skin [Valid Members (without RAWSKIN_ANIMATED): dwFlags   ::   Valid Members (with RAWSKIN_ANIMATED): dwFlags, nRegionCount, lphRegions].
#define RAWSKIN_LAYERED           0x00000002L       // Raw skin is a layered window skin [].

// Optional raw animation format
#define RAWSKIN_ANIMATED          0x00000002L       // Raw skin is a layered window skin.



// Public Structs
// ---------------

// Raw skin data struct
typedef struct tagRAWSKINDATA
{
  DWORD dwFlags;                                    // Flags that determine the type of raw skin
  
  // Regioned skin vars
  INT nRegionCount;                                 // How many regions exist in the regioned array [if animated skin]
  union {
    HRGN hRegion;                                   // The region
    HRGN *lphRegions;                               // The region array [if animated skin]
  };
  
  // Layered window skin vars

} RAWSKINDATA, *LPRAWSKINDATA;

// Create skin struct
typedef struct tagCREATESKINSTRUCT
{
  DWORD dwFlags;
  LPRAWSKINDATA lpRawSkin;
} CREATESKINSTRUCT, *LPCREATESKINSTRUCT;



// Public Functions
// -----------------

extern "C" {
  
  // Skin creation functions
  LPSKIN CreateSkin ();
  BOOL DestroySkin ( LPSKIN lpSkin );
  
  // Skin data functions
  BOOL SetSkinInfo ();
  
}

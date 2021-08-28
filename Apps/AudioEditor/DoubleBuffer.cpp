//=========================================================================
// DOUBLEBUFFER.CPP
//=========================================================================

//=========================================================================
// INCLUDES
//=========================================================================
#include "stdafx.h"
#include "DoubleBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//=========================================================================

CDoubleBuffer::CDoubleBuffer( CDC*& pDC )
{
    ASSERT( pDC );

    // Clear m_pDC in case anything fails to initialize
    m_pDC = NULL;

    // Get rect & size of window client
    pDC->GetWindow()->GetClientRect( &m_Rect );
    w = m_Rect.right  - m_Rect.left;
    h = m_Rect.bottom - m_Rect.top;

    // Create compatible DC and Bitmap
    if( m_BufferedDC.CreateCompatibleDC( pDC ) )
    {
        // Create bitmap
        if( m_BufferedBitmap.CreateCompatibleBitmap( pDC, w, h ) )
        {
            // Select new bitmap into DC
            m_pOldBitmap = m_BufferedDC.SelectObject( &m_BufferedBitmap );

            // Save old and set new DC pointer
            m_pDC = pDC;
            pDC = &m_BufferedDC;
        }
    }
}

//=========================================================================

CDoubleBuffer::CDoubleBuffer( CDC*& pDC, s32 AddWidth )
{
    ASSERT( pDC );

    // Clear m_pDC in case anything fails to initialize
    m_pDC = NULL;

    // Get rect & size of window client
    pDC->GetWindow()->GetClientRect( &m_Rect );
    w = (m_Rect.right  - m_Rect.left) + AddWidth ;
    h = m_Rect.bottom - m_Rect.top;

    // Create compatible DC and Bitmap
    if( m_BufferedDC.CreateCompatibleDC( pDC ) )
    {
        // Create bitmap
        if( m_BufferedBitmap.CreateCompatibleBitmap( pDC, w, h ) )
        {
            // Select new bitmap into DC
            m_pOldBitmap = m_BufferedDC.SelectObject( &m_BufferedBitmap );

            // Save old and set new DC pointer
            m_pDC = pDC;
            pDC = &m_BufferedDC;
        }
    }
}

//=========================================================================

CDoubleBuffer::~CDoubleBuffer( void )
{
    // Are we double buffered, if so blit to front buffer and prepare to kill double buffer
    if( m_pDC )
    {
        // Blit to front buffer
        m_pDC->BitBlt( 0, 0, w, h, &m_BufferedDC, 0, 0, SRCCOPY );

        // Remove bitmap so all can be destroyed correctly
        m_BufferedDC.SelectObject( m_pOldBitmap );
    }
}

//=========================================================================
const CRect& CDoubleBuffer::GetRect( void )
{
    return m_Rect;
}

//=========================================================================
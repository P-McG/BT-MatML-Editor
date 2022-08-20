/////////////////////////////////////////////////////////////////////////////
// Name:        samples/printing.h

// Purpose:     Printing demo for wxWidgets
// Author:      Julian Smart
// Modified by:
// Created:     1995
// RCS-ID:      $Id: printing.h 42522 2006-10-27 13:07:40Z JS $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#include "wx/metafile.h"
#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/image.h"
#include "wx/accel.h"


class MyPrintout: public wxPrintout
{
 public:
  MyPrintout(const wxChar *title = _T("My printout")):wxPrintout(title) {}
  bool OnPrintPage(int page);
  bool HasPage(int page);
  bool OnBeginDocument(int startPage, int endPage);
  void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);

//  void DrawPageOne();

//  void DrawPageTwo();

};

#define WXPRINT_QUIT            100
#define WXPRINT_PRINT           101
#define WXPRINT_PAGE_SETUP      103
#define WXPRINT_PREVIEW         104

#define WXPRINT_PRINT_PS        105
#define WXPRINT_PAGE_SETUP_PS   107
#define WXPRINT_PREVIEW_PS      108

#define WXPRINT_ABOUT           109

#define WXPRINT_ANGLEUP         110
#define WXPRINT_ANGLEDOWN       111

#ifdef __WXMAC__
    #define WXPRINT_PAGE_MARGINS 112
#endif

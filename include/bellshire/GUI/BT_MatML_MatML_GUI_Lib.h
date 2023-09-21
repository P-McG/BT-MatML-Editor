#pragma once
// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/config.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "bellshire/Lib/matml31_lib.hxx"
//#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/Lib/utilities/BT_MatML_Get_Associated_Lib_type.h"
//#include "bellshire/GUI/BT_MatML_MatMLLibDropTarget.h"
//#include "bellshire/GUI/Utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"
#include "bellshire/Lib/BT_MatML_MatML_Lib.h"

namespace bellshire::GUI{
    class MatMLLibDropTarget;
    template<class MatML> class Get_Associated_Lib_type;
    class TreeCtrlSorted;


    class MatML_GUI_Lib : public bellshire::Lib::MatML_Lib
    {
    public:
        
        template< class MatML_Lib_Class >
        inline static std::unique_ptr<MatML_Lib_Class> GetLib(
            const wxString& MatML_Lib_Filename
        );

        template< class MatML_Lib_Class >
        inline static void SetLib(
            std::unique_ptr<::xml_schema::element_type>& lib_element,
            const wxString& MatML_Lib_Filename
        );

        template< class MatML_Class,
            class MatML_Class_Base,
            class MatML_Lib_Class = bellshire::Lib::utilities::Get_Associated_Lib_type<MatML_Class>::MatML_Lib_type
        >
        inline static void UpdateLib(TreeCtrlSorted* MatMLLibTreeCtrl,
                observer_ptr<xml_schema::element_type> generic_lib_element
            );

        template< class MatML_Class,
            class MatML_Class_Base,
            class MatML_Lib_Class = bellshire::Lib::utilities::Get_Associated_Lib_type<MatML_Class>::MatML_Lib_type
        >
        inline static wxWindow* CreateLibPanel(wxWindow* parent,
                TreeCtrlSorted*& MatMLLibTreeCtrl,
                observer_ptr<xml_schema::element_type> lib_element,
                MatMLLibDropTarget*& droptarget
            );
    };

}//namespace bellshire
#include "bellshire/GUI/BT_MatML_MatML_GUI_Lib.inl"
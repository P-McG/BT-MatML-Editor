#pragma once

#include <wx/dnd.h>
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"
#include "bellshire/BT_MatML_Default.h"

namespace bellshire::GUI
{

    static wxString ShapeFormatId()
    {
        return "DF_ANYMATMLDATA";
    }

    class DnDMatMLDataObject;
    class DnDMatMLData;
    class DnDAnyMatMLData;
// ----------------------------------------------------------------------------
// DnDMatMLDataObject
// ----------------------------------------------------------------------------


    class DnDMatMLDataObject : public wxDataObject
    {
    public:
        DnDMatMLDataObject(DnDMatMLData* matmldata = (DnDMatMLData *) nullptr);
        virtual ~DnDMatMLDataObject();

        wxDataFormat GetPreferredFormat(Direction WXUNUSED(dir)) const;
        size_t GetFormatCount(Direction dir) const;
        void GetAllFormats(wxDataFormat* formats, Direction dir) const;
        size_t GetDataSize(const wxDataFormat& format) const;
        bool GetDataHere(const wxDataFormat& format, void* pBuf) const;
        bool SetData(const wxDataFormat& format, size_t WXUNUSED(len), const void* buf);
        DnDMatMLData* GetMatMLData();

    private:
        wxDataFormat m_dataformat;  // our custom format
        DnDMatMLData* m_matmldata;
    };

// ----------------------------------------------------------------------------
// DnDMatMLData
// ----------------------------------------------------------------------------

    class DnDMatMLData
    {
    public:
        enum Kind
        {
            None,
            MatML_TreeItemData
        };

        DnDMatMLData(const MatMLTreeItemData* data)
            :m_data(data)
        {};

        virtual ~DnDMatMLData() { /*delete m_data;*/ };

        // restore from buffer
        static DnDMatMLData* New(const void* buf);

        virtual size_t GetDataSize() const
        {
            return sizeof(MatMLDump);
        }

        virtual void GetDataHere(void* buf) const;

        // to implement in derived classes
        virtual Kind GetKind() const = 0;

        //Gives away ownership of the m_data
        const MatMLTreeItemData* GetMatMLTreeItemData() { auto rtn = m_data; m_data = nullptr; return rtn; }

        virtual bool IsNull() { return m_data==nullptr; }
    protected:

        struct MatMLDump
        {
            int k;
            MatMLTreeItemData* data;
        };

        const MatMLTreeItemData* m_data;
    };

    // ----------------------------------------------------------------------------
    // DnDUnitMatMLData
    // ----------------------------------------------------------------------------


    class DnDAnyMatMLData : public DnDMatMLData
    {
    public:
        DnDAnyMatMLData(const MatMLTreeItemData* data)
            : DnDMatMLData(data)
        {}

        virtual ~DnDAnyMatMLData(){ }

        virtual Kind GetKind() const wxOVERRIDE { return MatML_TreeItemData; }
        
    };

    //// ----------------------------------------------------------------------------
    //// DnDClassMatMLData
    //// ----------------------------------------------------------------------------


    //class DnDClassMatMLData : public DnDMatMLData
    //{
    //public:
    //    DnDClassMatMLData(const Unit* data)
    //        : DnDMatMLData(data)
    //    {}

    //    virtual ~DnDClassMatMLData() { }

    //    virtual Kind GetKind() const wxOVERRIDE { return MatML_Class; }

    //};
};//bellshire
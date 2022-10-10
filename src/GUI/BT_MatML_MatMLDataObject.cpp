#include "BT_MatML_MatMLDataObject.h"


using namespace bellshire;

DnDMatMLDataObject::DnDMatMLDataObject(DnDMatMLData* matmldata)
	:m_matmldata(nullptr)
{
	if (matmldata)
	{
		// we need to copy the shape because the one we're handled may be
		// deleted while it's still on the clipboard (for example) - and we
		// reuse the serialisation methods here to copy it
		void* buf = malloc(matmldata->DnDMatMLData::GetDataSize());
		matmldata->GetDataHere(buf);
		if(m_matmldata)
			delete m_matmldata;
		m_matmldata = DnDMatMLData::New(buf);

		free( buf);
	}
	else
	{
		// nothing to copy
		m_matmldata = nullptr;
	}

	// this string should uniquely identify our format, but is otherwise
	// arbitrary
	m_dataformat.SetId(ShapeFormatId());

}

DnDMatMLDataObject::~DnDMatMLDataObject()
{
	delete m_matmldata;
}

// implement base class pure virtuals
// ----------------------------------

wxDataFormat DnDMatMLDataObject::GetPreferredFormat(Direction WXUNUSED(dir)) const 
{
	return m_dataformat;
}

size_t DnDMatMLDataObject::GetFormatCount(Direction dir) const
{
	// our custom format is supported by both GetData() and SetData()
	size_t nFormats = 1;
	if (dir == Get)
	{
		/* for future use */
	}

	return nFormats;
}

void DnDMatMLDataObject::GetAllFormats(wxDataFormat* formats, Direction dir) const
{
	formats[0] = m_dataformat;
	if (dir == Get){/*future use*/ }
}

size_t DnDMatMLDataObject::GetDataSize(const wxDataFormat& format) const 
{
	if (format == m_dataformat)
	{
			return m_matmldata->GetDataSize();
	}
	return sizeof(nullptr);
}

bool DnDMatMLDataObject::GetDataHere(const wxDataFormat& format, void* pBuf) const
{
	if (format == m_dataformat)
	{
		m_matmldata->GetDataHere(pBuf);
		return true;
	}
	return false;
}


/// <summary>
/// Copy the data from the buffer, return true on success. 
/// Must be implemented in the derived class if the object supports setting its data.
/// </summary>
/// <param name="format"></param>
/// <param name="len"></param>
/// <param name="buf"></param>
/// <returns></returns>
bool DnDMatMLDataObject::SetData(const wxDataFormat& format, size_t WXUNUSED(len), const void* buf)
{
	if (format != m_dataformat) return false;

	delete m_matmldata; m_matmldata = nullptr;
	m_matmldata = DnDMatMLData::New(buf);

	return true;
}

DnDMatMLData* DnDMatMLDataObject::GetMatMLData()
{
	DnDMatMLData* matmldata = m_matmldata;
	
	m_matmldata = (DnDMatMLData*)nullptr;

	return matmldata;
}


DnDMatMLData* DnDMatMLData::New(const void* buf)
{
	const MatMLDump& dump = *(const MatMLDump*)buf;

	switch (dump.k)
	{
	case MatML_Unit:
		return new DnDUnitMatMLData(dump.data);
	default:
		return NULL;
	}
}

void DnDMatMLData::GetDataHere(void* buf) const
{
	MatMLDump& dump = *(MatMLDump*)buf;
	dump.data = const_cast<Unit*>(m_data);
	dump.k = GetKind();
}
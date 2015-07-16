#include <DexFrame_MC.h>

namespace Dex
{
	BEGIN_EVENT_TABLE(Frame, wxFrame)
		EVT_BUTTON(ID_GO, Frame::StartConvert)
	END_EVENT_TABLE()

	Frame::Frame(void)
		: wxFrame(NULL, ID_FRAME, wxT("Dex Mesh Converter"), wxDefaultPosition, wxSize(500, 300),
		wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL), Serializer("")
	{
		SetSizeHints(wxDefaultSize, wxDefaultSize);
		SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

		wxBoxSizer* Sizer_General;
		Sizer_General = new wxBoxSizer(wxVERTICAL);

		wxBoxSizer* bSizer3;
		bSizer3 = new wxBoxSizer(wxVERTICAL);

		m_FileSelect = new wxFilePickerCtrl(this, ID_FILESELECT, wxEmptyString, wxT("Select a file"), wxT("*.obj"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
		bSizer3->Add(m_FileSelect, 0, wxALL | wxEXPAND, 5);

		wxBoxSizer* Sizer_Setting;
		Sizer_Setting = new wxBoxSizer(wxHORIZONTAL);

		m_CheckBox_Vertex = new wxCheckBox(this, ID_CHECKBOX_VERTEX, wxT("Вершины"), wxDefaultPosition, wxDefaultSize, 0);
		m_CheckBox_Vertex->SetValue(true);
		Sizer_Setting->Add(m_CheckBox_Vertex, 0, wxALL, 5);

		m_CheckBox_Index = new wxCheckBox(this, ID_CHECKBOX_INDEX, wxT("Индексация"), wxDefaultPosition, wxDefaultSize, 0);
		m_CheckBox_Index->SetValue(true);
		Sizer_Setting->Add(m_CheckBox_Index, 0, wxALL, 5);

		m_CheckBox_Texcoord = new wxCheckBox(this, ID_CHECKBOX_TEXCOORD, wxT("Текстура"), wxDefaultPosition, wxDefaultSize, 0);
		Sizer_Setting->Add(m_CheckBox_Texcoord, 0, wxALL, 5);

		bSizer3->Add(Sizer_Setting, 1, wxEXPAND, 5);

		m_ProgressBar = new wxGauge(this, ID_PROGRESSBAR, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
		bSizer3->Add(m_ProgressBar, 0, wxALL | wxEXPAND, 5);

		m_Go = new wxButton(this, ID_GO, wxT("Convert"), wxDefaultPosition, wxSize(250, 45), 0);
		bSizer3->Add(m_Go, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

		Sizer_General->Add(bSizer3, 1, wxEXPAND | wxALL, 5);

		SetSizer(Sizer_General);
		Layout();

		Centre(wxBOTH);
	}

	Frame::~Frame(void)
	{
	}

	void Frame::InitEngine(void)
	{
		m_pCore = new Core();
	}

	void Frame::StartConvert(wxCommandEvent& pEvent)
	{
		string path = m_FileSelect->GetPath();

		if (path != "")
		{
			std::ifstream file;
			file.open(path.c_str(), std::ios::in);

			string line;

			if (file)
			{
				int nCount = 0;
				while (file)
				{
					file >> line;

					if (line == "v")
					{
						file.ignore();
						nCount++;
					}
					else if (line == "vt")
					{
						file.ignore();
						nCount++;
					}
					else if (line == "vn")
					{
						file.ignore();
						nCount++;
					}
					else if (line == "f")
					{
						file.ignore();
						nCount++;
					}
				}
				m_ProgressBar->SetRange(nCount);

				file.clear();
				file.seekg(0, std::ios::beg);

				vector< Point3 > position;
				vector< Point2 > texcoord;
				vector< Point3 > normal;

				nCount = 0;
				m_ProgressBar->SetValue(0);

				// Step 1
				while (file)
				{
					file >> line;

					if (line == "v")
					{
						float x, y, z;
						file >> x >> y >> z;
						m_ProgressBar->SetValue(nCount++);

						position.push_back(Point3(x, y, z));
					}
					else if (line == "vt")
					{
						float u, v;
						file >> u >> v;
						m_ProgressBar->SetValue(nCount++);

						texcoord.push_back(Point2(u, v));
					}
					else if (line == "vn")
					{
						float x, y, z;
						file >> x >> y >> z;
						m_ProgressBar->SetValue(nCount++);

						normal.push_back(Point3(x, y, z));
					}
					else if (line == "f")
					{
						int nPosition, nTexcoord, nNormal;
						OBJ_File vertex;

						m_ProgressBar->SetValue(nCount++);

						for (int nFace = 0; nFace < 3; nFace++)
						{
							ZeroMemory(&vertex, sizeof(OBJ_File));

							file >> nPosition;
							vertex.position = position[nPosition - 1];

							if ('/' == file.peek())
							{
								file.ignore();

								if ('/' != file.peek())
								{
									file >> nTexcoord;
									vertex.texcoord = texcoord[nTexcoord - 1];
								}

								if ('/' == file.peek())
								{
									file.ignore();

									file >> nNormal;
									vertex.normal = normal[nNormal - 1];
								}
							}

							int res = AddVertex(&vertex);
							m_lIndices.push_back(res);
						}
					}
				}
				file.close();

				// Step 2
				path = path.substr(0, path.length() - 3) + "dexg";

				// Step 3
				mPath = path;
				Serializer::Open(OPEN_MODE_WRITE | OPEN_MODE_BINARY);
				
				//enum GeometryStruct
				//{
				//	// int ( version visual object )
				//	// bool ( bUseIndex )
				//	// if ( bUseIndex )
				//	// {
				//	//		int ( enum IndexType )
				//	//		_intun ( Index count )
				//	//		Ptr ( buffer )
				//	// }
				//	GEOMETRY_VERTEX_BEGIN,
				//	// _intun ( Vertex count )
				//	GEOMETRY_VERTEX_ELEMENT_BEGIN,
				//	// int ( enum VertexSemantics )
				//	GEOMETRY_VERTEX_ELEMENT_END,
				//	// Ptr ( buffer )
				//	GEOMETRY_VERTEX_END
				//	// ASCII code shader
				//};

				WriteHeader(GEOMETRY_VERSION_CONVERTER);
				// Index
				WriteBool(true);
				WriteInt(IT_32);
				WriteUInt(m_lIndices.size());
				WritePtr(m_lIndices.data(), m_lIndices.size() * sizeof(unsigned long));

				// VS cso open
				ifstream read_shader_file("Data/SampleVertexShader.cso", ios::binary);

				vector<unsigned char> data_shader;
				while (read_shader_file)
				{
					BYTE byte_read = 0;
					read_shader_file.read((char*)&byte_read, sizeof(unsigned char));

					data_shader.push_back(byte_read);
				}

				read_shader_file.close();

				// vs
				WriteUInt(data_shader.size());
				WritePtr(data_shader.data(), data_shader.size());

				WriteHeader(GEOMETRY_VERTEX_ELEMENT_BEGIN);
				WriteInt(VL_POSITION);
				WriteHeader(GEOMETRY_VERTEX_ELEMENT_BEGIN);
				WriteInt(VL_TEXTURE);
				WriteHeader(GEOMETRY_VERTEX_ELEMENT_BEGIN);
				WriteInt(VL_NORMAL);
				WriteHeader(GEOMETRY_VERTEX_ELEMENT_END);

				// Vertex
				WriteUInt(m_lVertices.size());
				WritePtr(m_lVertices.data(), m_lVertices.size() * sizeof(OBJ_File));

				read_shader_file.open("Data/SamplePixelShader.cso", ios::binary);

				data_shader.clear();
				while (read_shader_file)
				{
					BYTE byte_read = 0;
					read_shader_file.read((char*)&byte_read, sizeof(unsigned char));

					data_shader.push_back(byte_read);
				}

				read_shader_file.close();

				// ps
				WriteUInt(data_shader.size());
				WritePtr(data_shader.data(), data_shader.size());

				Serializer::Close();
			}
		}
	}

	int Frame::AddVertex(OBJ_File* sVertex)
	{
		int res = -1;

		for (size_t i = 0; i < m_lVertices.size(); i++)
		{
			if (memcmp(&m_lVertices[i], sVertex, sizeof(OBJ_File)) == 0)
			{
				res = i;
			}
		}

		if (res < 0)
		{
			res = m_lVertices.size();
			m_lVertices.push_back(*sVertex);
		}

		return res;
	}
}
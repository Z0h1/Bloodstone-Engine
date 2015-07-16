#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <io.h>

#include <vector>
#include <list>
#include <map>

#pragma warning ( disable : 4251 )

using namespace std;

namespace Dex
{
	// D_EXPORT
	#if defined ( BLOODCORE_EXPORTS )
	#	define D_EXPORT __declspec( dllexport )
	#else
	#	define D_EXPORT __declspec( dllimport )
	#endif

	typedef float Point;
	typedef unsigned int _intun;
	typedef unsigned short UInt16;

	#define OPEN_MODE_READ		0x01
	#define OPEN_MODE_WRITE		0x04
	#define OPEN_MODE_BINARY	0x08

	// Classes
	class IInputSystem;
	class IInputDevice;
	class VertexBuffer;
	class IndexBuffer;
	class CoreComponent;
	class RenderComponent;
	class CameraComponent;
	class LightComponent;
	class GeometryFile;
	class ResourceManager;
	class Folder;
	class CoreFile;
	class File;
	class Core;
	class SceneObject;
	class Serializer;
	class Scene;
	class Log;
	class RenderSystem;
	class ConfigFile;
	class StringConverter;
	class DynamicLibrary;
	class RenderWindow;
	class IRenderConnect;
	class ISystem;
	class FileSystem;
	class CoreObject;
	class Point4;
	class Point3;
	class Point2;
	class FileSystem;

	typedef map<string, string>			_lParametor;
	typedef vector<string>				_lString;
	typedef map<string, CoreFile*>		_lCoreFile;

	// FileSystem
	enum FileFormat // CoreFile
	{
		FF_UNKNOWN,		// NULL
		FF_FOLDER,		// Folder
		FF_DEXG,		// DEX Geometry *.dexg
		FF_DEXM,		// DEX Material *.dexm
		FF_DEXP,		// DEX Pack *.dexp
		FF_DEXVOI,		// DEX visual Object info *.dexvoi
		FF_DEXS			// DEX Shader *.dexs
	};
	enum FolderType
	{
		FT_FOLDER,		// Folder
		FT_DEXP,		// DEX Pack *.dexp
		FT_ZIP			// zip pack *.zip
	};

	enum SystemsType
	{
		SYSTEM_RENDER_DIRECTX_9,
		SYSTEM_RENDER_DIRECTX_11,
		SYSTEM_RENDER_DIRECTX_11_1,
		SYSTEM_RENDER_DIRECTX_11_2,
		SYSTEM_INPUT_DX,
		SYSTEM_FILE_DEX
	};

	enum MessageTypes
	{
		NORMAL,
		MT_WARNING,
		MT_ERROR
	};

	enum WorkPriority
	{
		// TODO tharde
		WP_MAIN,
		WP_COLLECTION,
		WP_FILE,
		WP_SYSTEM,
		WP_STEP_1,
		WP_STEP_2,
		WP_STEP_3,
		WP_STEP_4,
		WP_COMPONENT,
		WP_END
	};

	enum InputDeviceType
	{
		IDT_Mouse,
		IDT_Keyboard
	};

	enum PrimitiveType
	{
		PT_NULL,
		PT_POINT,
		PT_LINE,
		PT_POLYGON,
	};

	enum OpenMode
	{
		OM_READ,
		OM_WRITE
	};

	enum IndexType
	{
		IT_16,
		IT_32
	};

	enum SceneObjectType
	{
		SOT_NULL,
		SOT_LIGHT,
		SOT_CAMERA,
		SOT_MESH,
		SOT_GROUP
	};

	enum LightType
	{
		LT_SPORT
	};

	enum ObjectComponentType
	{
		OCT_RENDER,
		OCT_CAMERA,
		OCT_LIGHT
	};

	#define VL_OFFSET_POSITION(offset) offset += 12;
	#define VL_OFFSET_NORMAL(offset) offset += 12;
	#define VL_OFFSET_TEXTURE(offset) offset += 8;

	enum VertexLayout
	{
		VL_POSITION,
		VL_NORMAL,
		VL_TEXTURE
	};
}
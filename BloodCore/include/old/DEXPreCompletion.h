#pragma once

#include "DEXPlatform.h"

typedef unsigned char       DEX_BYTE;
typedef unsigned short      DEX_WORD;
typedef unsigned long		DEX_DWORD;
typedef int                 DEX_INT;
typedef unsigned int        DEX_UINT;
typedef void	            *DEX_PVOID;

#define DEX_MAX_INT			0xffffffff // 4 Byte

struct DEXMemory
{
	DEX_PVOID pFirstAddres;
	DEX_UINT nCountBlock;
	DEX_UINT nSizeOneBlock;
};
typedef DEXMemory			*DEX_PMemory;

typedef class DEXCore		*DEX_PCore;
typedef class DEXClass		*DEX_PClass;
typedef class DEXSystem		*DEX_PSystem;

// D11_2 D_10_1 D12 OGL_2
#define DEX_USES_GRAPHIC_SYSTEM D11_2

#if defined ( BLOODCORE_EXPORTS )
#	define DEX_EXPORT __declspec( dllexport )
#else
#	define DEX_EXPORT __declspec( dllimport )
#endif

namespace DEX
{
	

	// MATH BEGIN

	typedef float _point;
	typedef unsigned int _32un;
	typedef unsigned short _16un;

	class _4point;
	class _3point;
	class _2point;
	class _3DMatrix;
	class _3DVector;

	// MATH END

	#define OPEN_MODE_READ		0x01
	#define OPEN_MODE_WRITE		0x04
	#define OPEN_MODE_BINARY	0x08

	// Classes
	class InputSystem;
	class InputDevice;
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
#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <io.h>
#include <iomanip>
#include <sstream>

#include <algorithm>

#include <assert.h>

#include <vector>
#include <list>
#include <map>

#include <Windows.h>

#pragma warning ( disable : 4251 )

namespace Dex
{
	// D_EXPORT
	#if defined ( BLOODCORE_EXPORTS )
	#	define D_EXPORT __declspec( dllexport )
	#else
	#	define D_EXPORT __declspec( dllimport )
	#endif

	typedef float Point;
	typedef unsigned int UInt32;
	typedef unsigned short UInt16;

	// String
	typedef std::string String;
	typedef std::stringstream StringStream;
	typedef std::ofstream OFStream;
	typedef std::ifstream IFStream;

	// Classes
	class IInputSystem;
	class IInputDevice;
	class HardwareBufferData;
	class HardwareVertexBuffer;
	class HardwareIndexBuffer;
	class ObjectLocation;
	class ObjectComponent;
	class RenderComponent;
	class CameraComponent;
	class LightComponent;
	class ArchiveFactory;
	class FileArchive;
	class ZipAchive;
	class ResourceManager;
	class Core;
	class SceneObject;
	class Scene;
	class Log;
	class IRenderSystem;
	class ConfigFile;
	class StringConverter;
	class DynamicLibrary;
	class IRenderWindow;
	class IRenderConnect;
	class ISystem;

	enum SystemsType
	{
		RENDER_SYSTEM_DIRECTX_9,
		RENDER_SYSTEM_DIRECTX_11,
		INPUT_SYSTEM_DX
	};

	enum MessageTypes
	{
		NORMAL,
		WARNING,
		EZ_ERROR
	};

	enum WorkPriority
	{
		// TODO tharde
		WP_MAIN,
		WP_COLLECTION,
		WP_SYSTEM,
		WP_STEP_1,
		WP_STEP_2,
		WP_STEP_3,
		WP_STEP_4,
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

	enum ArchiveType
	{
		AT_FILE,
		AT_ZIP
	};

	enum VertexSemantics
	{
		VS_POSITION,
		VS_NORMAL,
		VS_TEX
	};
}
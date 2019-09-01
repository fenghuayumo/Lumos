#pragma once
#include "LM.h"
#include "Maths/Maths.h"

namespace Lumos
{
	namespace Graphics
	{
		class Pipeline;
		class CommandBuffer;
		class DescriptorSet;
		class Swapchain;
		class IndexBuffer;
		class VertexArray;
		class Mesh;

		enum LUMOS_EXPORT RendererBufferType
		{
			RENDERER_BUFFER_NONE = 0,
			RENDERER_BUFFER_COLOUR = BIT(0),
			RENDERER_BUFFER_DEPTH = BIT(1),
			RENDERER_BUFFER_STENCIL = BIT(2)
		};

		enum class LUMOS_EXPORT DrawType
		{
			POINT,
			TRIANGLE,
			LINES
		};

		enum class LUMOS_EXPORT StencilType
		{
			EQUAL,
			NOTEQUAL,
			KEEP,
			REPLACE,
			ZERO,
			ALWAYS
		};

		enum class LUMOS_EXPORT PixelPackType
		{
			PACK,
			UNPACK
		};

		enum class LUMOS_EXPORT RendererBlendFunction
		{
			NONE,
			ZERO,
			ONE,
			SOURCE_ALPHA,
			DESTINATION_ALPHA,
			ONE_MINUS_SOURCE_ALPHA
		};

		enum class LUMOS_EXPORT RendererBlendEquation
		{
			NONE,
			ADD,
			SUBTRACT
		};

		enum class LUMOS_EXPORT RenderMode
		{
			FILL,
			WIREFRAME
		};

		enum class LUMOS_EXPORT DataType
		{
			FLOAT,
			UNSIGNED_INT,
			UNSIGNED_BYTE
		};

		class LUMOS_EXPORT Renderer
		{
		public:
			Renderer()
			{
			}

			virtual ~Renderer() = default;

			static void Init(u32 width, u32 height);
			static void Release();
			virtual void InitInternal() = 0;
			virtual void Begin() = 0;
			virtual void OnResize(u32 width, u32 height) = 0;
			inline static Renderer* GetRenderer() { return s_Instance; }

			virtual void PresentInternal() = 0;
			virtual void PresentInternal(Graphics::CommandBuffer* cmdBuffer) = 0;
			virtual void BindDescriptorSetsInternal(Graphics::Pipeline* pipeline, Graphics::CommandBuffer* cmdBuffer, u32 dynamicOffset, std::vector<Graphics::DescriptorSet*>& descriptorSets) = 0;

			virtual const String& GetTitleInternal() const = 0;
			virtual void DrawIndexedInternal(CommandBuffer* commandBuffer, DrawType type, u32 count, u32 start) const = 0;
			virtual void DrawInternal(CommandBuffer* commandBuffer, DrawType type, u32 count, DataType datayType, void* indices) const = 0;
			virtual Graphics::Swapchain* GetSwapchainInternal() const = 0;

			inline static void Present() { s_Instance->PresentInternal(); }
			inline static void Present(Graphics::CommandBuffer* cmdBuffer) { s_Instance->PresentInternal(cmdBuffer); }
			inline static void BindDescriptorSets(Graphics::Pipeline* pipeline, Graphics::CommandBuffer* cmdBuffer, u32 dynamicOffset, std::vector<Graphics::DescriptorSet*>& descriptorSets) { s_Instance->BindDescriptorSetsInternal(pipeline, cmdBuffer, dynamicOffset, descriptorSets); }
			inline static void Draw(CommandBuffer* commandBuffer, DrawType type, u32 count, DataType datayType = DataType::UNSIGNED_INT, void* indices = nullptr) { s_Instance->DrawInternal(commandBuffer, type, count, datayType, indices); }
			inline static void DrawIndexed(CommandBuffer* commandBuffer, DrawType type, u32 count, u32 start = 0) { s_Instance->DrawIndexedInternal(commandBuffer, type, count, start); }
			inline static const String& GetTitle() { return s_Instance->GetTitleInternal(); }

			inline static Swapchain* GetSwapchain() { return s_Instance->GetSwapchainInternal(); }
            
        protected:
            static Renderer* (*CreateFunc)(u32, u32);
            
            static Renderer* s_Instance;
		};
	}
}


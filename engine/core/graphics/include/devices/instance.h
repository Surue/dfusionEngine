#pragma once

#include <vulkan/vulkan.h>

#include <vector>

#ifdef NDEBUG
constexpr bool kEnableValidationLayers = false;
#else
constexpr bool kEnableValidationLayers = true;
#endif

namespace dfe {
class Window;

namespace graphics {
class Instance {
 public:
  friend VKAPI_ATTR VkBool32 VKAPI_CALL
  DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

  static const std::vector<const char*> kValidationLayers;
  static const std::vector<const char*> kInstanceExtensions;
  static const std::vector<const char*> kDeviceExtensions;

  explicit Instance(const Window& window);
  ~Instance();

  /**
   * \brief Create a Debug Messenger specialized for vulkan layer validation
   * \param instance
   * \param pCreateInfo
   * \param pAllocator
   * \param pDebugMessenger
   * \return
   */
  static VkResult CreateDebugUtilsMessengerEXT(
      const VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
      const VkAllocationCallbacks* pAllocator,
      VkDebugUtilsMessengerEXT* pDebugMessenger);

  /**
   * \brief Destroy the layer validation's messenger
   * \param instance
   * \param debugMessenger
   * \param pAllocator
   */
  static void DestroyDebugUtilsMessengerEXT(
      VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
      const VkAllocationCallbacks* pAllocator);

  /**
   * \brief Function to bind ressources to the instances from a descriptor set
   * \param device
   * \param commandBuffer
   * \param pipelineBindPoint
   * \param layout
   * \param set
   * \param descriptorWriteCount
   * \param pDescriptorSet
   */
  static void CmdPushDescriptorSetKhr(
      VkDevice device, VkCommandBuffer commandBuffer,
      VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout,
      uint32_t set, uint32_t descriptorWriteCount,
      const VkWriteDescriptorSet* pDescriptorSet);

  /**
   * \brief Return of the memory index for a certain type of memory
   * \param deviceMemoryProperties
   * \param memoryRequirements
   * \param requiredProperties
   * \return
   */
  static uint32_t FindMemoryTypeIndex(
      const VkPhysicalDeviceMemoryProperties& deviceMemoryProperties,
      const VkMemoryRequirements& memoryRequirements,
      VkMemoryPropertyFlags requiredProperties);

  static bool GetEnableValidationLayers() { return kEnableValidationLayers; }

  const std::vector<const char*>& GetInstanceLayers() const;

  const std::vector<const char*>& GetInstanceExtensions() const;

  const std::vector<const char*>& GetDeviceExtensions() const;

  const VkInstance& GetVkInstance() const { return _instance; }

 private:
  void SetupLayers();
  void SetupExtensions(const Window& window);
  void CreateInstance();
  void CreateDebugCallback();

  std::vector<const char*> _instanceLayer;
  std::vector<const char*> _instanceExtensions;
  std::vector<const char*> _deviceExtensions;

  VkDebugUtilsMessengerEXT _debugMessenger;
  VkInstance _instance;
};
}  // namespace graphics
}  // namespace dfe
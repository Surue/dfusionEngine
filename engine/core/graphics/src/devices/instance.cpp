#include <devices/instance.h>
#include <log.h>
#include <vulkan_error_error.h>
#include <window.h>

#include <iostream>

namespace dfe::graphics {
const std::vector<const char*> Instance::kValidationLayers = {
    "VK_LAYER_KHRONOS_validation"};
const std::vector<const char*> Instance::kInstanceExtensions = {
    VK_KHR_SURFACE_EXTENSION_NAME};
const std::vector<const char*> Instance::kDeviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

VkBool32 DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
  std::string war = "Vulkan";

  switch (messageSeverity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      war += "[War] : ";
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      war += "[Err] : ";
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
      break;
    default:
      break;
  }

  war += pCallbackData->pMessage;
  Debug::LogWarning(war);
  return VK_FALSE;
}

Instance::Instance(const Window& window)
    : _debugMessenger(VK_NULL_HANDLE), _instance(VK_NULL_HANDLE) {
  SetupLayers();
  SetupExtensions(window);
  CreateInstance();
  CreateDebugCallback();
}

Instance::~Instance() {
  DestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
  vkDestroyInstance(_instance, nullptr);
}

VkResult Instance::CreateDebugUtilsMessengerEXT(
    const VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger) {
  const auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
      vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }

  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void Instance::DestroyDebugUtilsMessengerEXT(
    const VkInstance instance, const VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator) {
  const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
      vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

void Instance::CmdPushDescriptorSetKhr(
    const VkDevice device, const VkCommandBuffer commandBuffer,
    const VkPipelineBindPoint pipelineBindPoint, const VkPipelineLayout layout,
    const uint32_t set, const uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorSet) {
  const auto func = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(
      vkGetDeviceProcAddr(device, "vkCmdPushDescriptorSetKHR"));

  if (func != nullptr) {
    func(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount,
         pDescriptorSet);
  }
}

uint32_t Instance::FindMemoryTypeIndex(
    const VkPhysicalDeviceMemoryProperties& deviceMemoryProperties,
    const VkMemoryRequirements& memoryRequirements,
    const VkMemoryPropertyFlags requiredProperties) {
  for (uint32_t i = 0; i < deviceMemoryProperties.memoryTypeCount; ++i) {
    if (memoryRequirements.memoryTypeBits & (1 << i)) {
      if ((deviceMemoryProperties.memoryTypes[i].propertyFlags &
           requiredProperties) == requiredProperties) {
        return i;
      }
    }
  }
  return -1;
}

const std::vector<const char*>& Instance::GetInstanceLayers() const {
  return _instanceLayer;
}

const std::vector<const char*>& Instance::GetInstanceExtensions() const {
  return _instanceExtensions;
}

const std::vector<const char*>& Instance::GetDeviceExtensions() const {
  return _deviceExtensions;
}

void Instance::SetupLayers() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (auto layerName : kValidationLayers) {
    auto layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      Debug::LogError("Vulkan validation layer not found");
    }

    _instanceLayer.emplace_back(layerName);
  }

  for (const auto& layerName : kDeviceExtensions) {
    _deviceExtensions.emplace_back(layerName);
  }
}

void Instance::SetupExtensions(const Window& window) {
  uint32_t extensionCount = 0;

  std::vector<const char*> extensions = window.GetVulkanExtensions();
  // If debug mod, add an extension to handle error
  if (kEnableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  for (const auto& instanceExtension : extensions) {
    _instanceExtensions.push_back(instanceExtension);
  }
  for (const auto& instanceExtension : kInstanceExtensions) {
    _instanceExtensions.push_back(instanceExtension);
  }
}

void Instance::CreateInstance() {
  // Create application info, use by the driver to do some optimization
  VkApplicationInfo appInfo = {};  // pNext = nullptr
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Vulkan application";
  appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  appInfo.pEngineName = "dFusionEngine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_2;

  // Store data for creating an instance
  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  // Set the layer for the api to be use by the sdl window
  auto extensions = _instanceExtensions;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  if (kEnableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(_instanceLayer.size());
    createInfo.ppEnabledLayerNames = _instanceLayer.data();
  }

  CheckVk(vkCreateInstance(&createInfo, nullptr, &_instance));
}

void Instance::CreateDebugCallback() {
  if (!kEnableValidationLayers) return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = DebugCallback;

  CheckVk(CreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr,
                                       &_debugMessenger));
}
}  // namespace dfe::graphics

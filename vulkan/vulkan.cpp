#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <optional>
#include <set>

// 정점 구조체
struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription binding{};
        binding.binding = 0;
        binding.stride = sizeof(Vertex);
        binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return binding;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attrs{};
        attrs[0].binding = 0;
        attrs[0].location = 0;
        attrs[0].format = VK_FORMAT_R32G32_SFLOAT;
        attrs[0].offset = offsetof(Vertex, pos);

        attrs[1].binding = 0;
        attrs[1].location = 1;
        attrs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attrs[1].offset = offsetof(Vertex, color);

        return attrs;
    }
};

// 사각형 정점
const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // 빨강
    {{0.5f, -0.5f},  {1.0f, 0.5f, 0.0f}}, // 주황
    {{0.5f, 0.5f},   {1.0f, 1.0f, 0.0f}}, // 노랑
    {{-0.5f, 0.5f},  {0.0f, 1.0f, 0.0f}}, // 초록
};
const std::vector<uint16_t> indices = { 0, 1, 2, 2, 3, 0 };

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// 바이너리 셰이더 파일 로드
std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file) throw std::runtime_error("failed to open file!");

    size_t size = (size_t)file.tellg();
    std::vector<char> buffer(size);

    file.seekg(0);
    file.read(buffer.data(), size);
    return buffer;
}

// (중략) Vulkan 초기화 관련 함수들: 인스턴스 생성, 디바이스 선택, 스왑체인 생성 등

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Rainbow Rectangle", nullptr, nullptr);

    // Vulkan 인스턴스 생성
    // 물리 디바이스, 논리 디바이스, 스왑체인, 이미지뷰, 렌더패스 생성
    // 셰이더 모듈 생성 (readFile + vkCreateShaderModule)
    // 파이프라인 설정: Vertex::getBindingDescription(), getAttributeDescriptions()
    // 버퍼 생성: vertexBuffer, indexBuffer

    // 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 커맨드 버퍼 기록
        // - 렌더 패스 시작
        // - 파이프라인 바인딩
        // - 정점 버퍼, 인덱스 버퍼 바인딩
        // - vkCmdDrawIndexed
        // - 렌더패스 종료
        // 제출 & 프레젠트
    }

    // 리소스 정리: 버퍼, 파이프라인, 셰이더 모듈, 스왑체인, 디바이스, 인스턴스 등
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

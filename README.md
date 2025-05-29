# quiz2

1.
그래픽스의 기초와 개념등의 이론과 opengl, webgl, p5.js Three.js, vulkan, r3f, ml5.js 등의 사용법을 배웠고 무지개 삼각형을 생성하는것부터 시작해 다양한 실습과 과제로 쉐이더, 재질 조명 등등과 다양한 객체를 생성하는 것을 배웠고 또한 ai를 사용해 웹캠을 사용하여 얼굴을 인식하여 표정이나 눈 깜빡임을 인식하는 프로그램을 코딩해보았고 전반적으로 그래픽스가 어떻게 이루어져있는지를 알게 되었다.

2.
P5.js를 통해 원기둥이 늘었다 줄었다를 반복하면서 움직이는 코드를 작성하면서 webgl을 학습하였고 p5.js를 활용해 팀별 웹용 3D작품을 만드는 팀 프로젝트를 통해 p5.js를 학습하였다. three.js 강좌를 들으며 정리하면서 학습하고 추가적으로 팀 프로젝트를 통해 객채를 생성하고 텍스쳐를 입히는 역할을 맡아 수행하면서 three.js를 학습하였다. Opencv를 활용하여 얼굴을 추출하는 실습을하였고, face-api를 사용해 사진을 넣어 얼굴을 인식하는 코드를 작성해 보았고 ai그래픽스를 활용한 나만의 비즈니스 플랜을 작성해 보았다.

3-1
Vulkan SDK 설치: https://vulkan.lunarg.com/

Visual Studio 프로젝트 속성:
C/C++ > 일반 > 추가 포함 디렉터리: $(VULKAN_SDK)\Include
링커 > 일반 > 추가 라이브러리 디렉터리: $(VULKAN_SDK)\Lib
링커 > 입력 > 추가 종속성: vulkan-1.lib

main.cpp 예제코드

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
const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

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

NuGet으로 GLFW 설치

Visual Studio에서 shaders 폴더를 만들고 그 속에 다음 2개의 파일(vert.glsl, frag.glsl)을 생성한다.

쉐이더 SPIR-V 컴파일
glslc vert.glsl -o vert.spv
glslc frag.glsl -o frag.spv

속성 페이지 > 구성 속성 > C/C++ > 언어 > C++ 언어 표준 → [ ISO C++17 표준 (/std:c++17) ] 이상 버전을 선택

3-2
vscode를 실행

index.html파일 생성 및 예제 코드

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Rainbow Rectangle (WebGL)</title>
  <style>
    body { margin: 0; }
    canvas { display: block; width: 100vw; height: 100vh; }
  </style>
</head>
<body>
<canvas id="glcanvas"></canvas>

<script type="text/javascript">
  const canvas = document.getElementById("glcanvas");
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;

  const gl = canvas.getContext("webgl");
  if (!gl) {
    alert("WebGL을 지원하지 않습니다.");
  }

  // 정점 셰이더
  const vsSource = `
    attribute vec2 aPosition;
    attribute vec3 aColor;
    varying vec3 vColor;
    void main() {
      gl_Position = vec4(aPosition, 0.0, 1.0);
      vColor = aColor;
    }
  `;

  // 프래그먼트 셰이더
  const fsSource = `
    precision mediump float;
    varying vec3 vColor;
    void main() {
      gl_FragColor = vec4(vColor, 1.0);
    }
  `;

  function createShader(gl, type, source) {
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      console.error("셰이더 컴파일 오류:", gl.getShaderInfoLog(shader));
      gl.deleteShader(shader);
      return null;
    }
    return shader;
  }

  function createProgram(gl, vsSource, fsSource) {
    const vertexShader = createShader(gl, gl.VERTEX_SHADER, vsSource);
    const fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fsSource);

    const program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);
    gl.linkProgram(program);
    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
      console.error("프로그램 링크 오류:", gl.getProgramInfoLog(program));
      return null;
    }
    return program;
  }

  const program = createProgram(gl, vsSource, fsSource);
  gl.useProgram(program);

  // 사각형 정점 위치 (좌하, 좌상, 우하, 우상)
  const positions = new Float32Array([
    -0.8, -0.8,  // 좌하
    -0.8,  0.8,  // 좌상
     0.8, -0.8,  // 우하
     0.8,  0.8   // 우상
  ]);

  // 각 정점에 대응하는 무지개 색상
  const colors = new Float32Array([
    1.0, 0.0, 0.0,  // 빨강
    1.0, 0.5, 0.0,  // 주황
    0.0, 0.0, 1.0,  // 파랑
    0.0, 1.0, 0.0   // 초록
  ]);

  // 인덱스 (두 개의 삼각형으로 사각형 구성)
  const indices = new Uint16Array([
    0, 1, 2,
    2, 1, 3
  ]);

  // 위치 버퍼
  const positionBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, positions, gl.STATIC_DRAW);
  const posAttrib = gl.getAttribLocation(program, "aPosition");
  gl.enableVertexAttribArray(posAttrib);
  gl.vertexAttribPointer(posAttrib, 2, gl.FLOAT, false, 0, 0);

  // 색상 버퍼
  const colorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, colors, gl.STATIC_DRAW);
  const colAttrib = gl.getAttribLocation(program, "aColor");
  gl.enableVertexAttribArray(colAttrib);
  gl.vertexAttribPointer(colAttrib, 3, gl.FLOAT, false, 0, 0);

  // 인덱스 버퍼
  const indexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

  // 화면 초기화 및 그리기
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);
  gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_SHORT, 0);
</script>
</body>
</html>

vscode 확장에서 live Server을 다운로드 후 코드 실행

3-2
vscode를 실행

index.html파일 생성 및 예제 코드

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Rainbow Square with WebGPU</title>
  <style>
    body { margin: 0; background: #000; }
    canvas { width: 100vw; height: 100vh; display: block; }
  </style>
</head>
<body>
<canvas id="webgpu-canvas"></canvas>
<script type="module">
  async function initWebGPU() {
    if (!navigator.gpu) {
      alert("WebGPU is not supported on this browser.");
      return;
    }

    const canvas = document.getElementById("webgpu-canvas");
    const adapter = await navigator.gpu.requestAdapter();
    const device = await adapter.requestDevice();
    const context = canvas.getContext("webgpu");

    const format = navigator.gpu.getPreferredCanvasFormat();
    context.configure({
      device,
      format,
      alphaMode: "opaque"
    });

    // 정점 데이터: 위치(x, y) + 색상(r, g, b)
    const vertexData = new Float32Array([
      // x, y,        r, g, b
      -0.5, -0.5,   1, 0, 0,  // 빨강
       0.5, -0.5,   1, 0.5, 0, // 주황
       0.5,  0.5,   1, 1, 0,  // 노랑
      -0.5,  0.5,   0, 0, 1,  // 파랑
    ]);

    const indexData = new Uint16Array([
      0, 1, 2,
      2, 3, 0
    ]);

    const vertexBuffer = device.createBuffer({
      size: vertexData.byteLength,
      usage: GPUBufferUsage.VERTEX | GPUBufferUsage.COPY_DST,
    });
    device.queue.writeBuffer(vertexBuffer, 0, vertexData);

    const indexBuffer = device.createBuffer({
      size: indexData.byteLength,
      usage: GPUBufferUsage.INDEX | GPUBufferUsage.COPY_DST,
    });
    device.queue.writeBuffer(indexBuffer, 0, indexData);

    const shaderModule = device.createShaderModule({
      code: `
        struct VertexOutput {
          @builtin(position) Position : vec4f,
          @location(0) color : vec3f
        };

        @vertex
        fn vs_main(
          @location(0) pos: vec2f,
          @location(1) color: vec3f
        ) -> VertexOutput {
          var out: VertexOutput;
          out.Position = vec4f(pos, 0.0, 1.0);
          out.color = color;
          return out;
        }

        @fragment
        fn fs_main(
          @location(0) color: vec3f
        ) -> @location(0) vec4f {
          return vec4f(color, 1.0);
        }
      `
    });

    const pipeline = device.createRenderPipeline({
      layout: "auto",
      vertex: {
        module: shaderModule,
        entryPoint: "vs_main",
        buffers: [
          {
            arrayStride: 5 * 4,
            attributes: [
              { shaderLocation: 0, offset: 0, format: "float32x2" }, // pos
              { shaderLocation: 1, offset: 2 * 4, format: "float32x3" }, // color
            ],
          },
        ],
      },
      fragment: {
        module: shaderModule,
        entryPoint: "fs_main",
        targets: [{ format }],
      },
      primitive: {
        topology: "triangle-list",
      },
    });

    function frame() {
      const commandEncoder = device.createCommandEncoder();
      const textureView = context.getCurrentTexture().createView();
      const renderPass = commandEncoder.beginRenderPass({
        colorAttachments: [{
          view: textureView,
          clearValue: { r: 0, g: 0, b: 0, a: 1 },
          loadOp: "clear",
          storeOp: "store",
        }],
      });

      renderPass.setPipeline(pipeline);
      renderPass.setVertexBuffer(0, vertexBuffer);
      renderPass.setIndexBuffer(indexBuffer, "uint16");
      renderPass.drawIndexed(6);
      renderPass.end();

      device.queue.submit([commandEncoder.finish()]);
      requestAnimationFrame(frame);
    }

    requestAnimationFrame(frame);
  }

  initWebGPU();
</script>
</body>
</html>

vscode 확장에서 live Server을 다운로드 후 코드 실행

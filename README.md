# PharmacySystem
本项目是一个基于 C++ 和 Qt 框架开发的桌面应用程序，旨在提供一个简单易用的药店药品管理解决方案。系统支持药品信息的录入、查询、销售以及销售数据的统计和管理。

## 项目背景

该项目是“面向对象程序设计B”课程的综合性设计性实验，旨在通过实践加深对面向对象编程思想的理解和应用，并熟悉使用 Qt 进行GUI应用程序开发。

## 主要功能

* **药品信息管理:**
    * **药品入库 (Add Medicine):** 添加新的药品信息，包括药品编号、名称、类别、生产厂家、价格、库存数量、生产日期和保质期。
    * **药品查询 (Search Medicine):** 支持通过药品名称或编号进行模糊搜索，快速定位药品。
    * **药品信息展示:** 以表格形式清晰展示所有药品的详细信息，包括生产日期和保质期。
* **药品销售管理:**
    * **药品销售 (Sell Medicine):** 选择药品并输入销售数量，系统自动更新库存。
    * **销售记录:** 自动记录每一笔销售，包括药品ID、销售时间和数量。
* **数据统计与分析:**
    * **销售统计 (Show Statistics):** 按不同时间维度（今日、本月、本季度、本年）统计各类别药品的销售总额。
* **数据管理:**
    * **数据清除 (Clear Data):** 提供清除销售记录、清除库存数据或清除所有数据的选项，并有操作确认提示。
    * **数据持久化:** 药品信息和销售记录会自动保存到本地文件，并在程序启动时加载。

## 技术栈

* **编程语言:** C++
* **GUI框架:** Qt (本项目中使用的特性兼容 Qt 5 和 Qt 6)
* **数据存储:** 本地文本文件 (`.dat`)，以CSV类似格式存储。
* **文件系统操作:** 使用 C++17 `std::filesystem` 进行目录创建。

## 系统设计

系统采用面向对象的设计思想，主要包含以下核心类：

* `Medicine`: 表示药品实体，封装药品属性和相关操作（如判断是否过期、是否临近保质期）。
* `Database`: 负责数据的存储与检索，包括药品信息和销售记录的读写操作，以及与数据文件的交互。实现了数据的加载、保存和清除逻辑。
* `PharmacySystem`: 主窗口类，负责构建用户界面、处理用户交互事件（如按钮点击），并协调其他类完成各项功能。
* `AddMedicineDialog`: 用于添加新药品的对话框界面类。
* `SellMedicineDialog`: 用于执行药品销售操作的对话框界面类。
* `StatisticsDialog`: 用于展示销售统计数据的对话框界面类。

## 文件结构 (简要)

PharmacySystem_project/
├── data/                     # 数据存储目录 (程序运行时根据需要自动创建)

│   ├── medicines.dat         # 存储药品信息

│   └── sales.dat             # 存储销售记录

├── AddMedicineDialog.cpp     # 添加药品对话框实现

├── AddMedicineDialog.h       # 添加药品对话框定义

├── Database.cpp              # 数据库类实现 (此项目中为空，主要逻辑在.h)

├── Database.h                # 数据库类定义及内联实现

├── Medicine.cpp              # 药品类实现 (此项目中为空，主要逻辑在.h)

├── Medicine.h                # 药品类定义及内联实现

├── PharmacySystem.cpp        # 主窗口类实现

├── PharmacySystem.h          # 主窗口类定义

├── SellMedicineDialog.cpp    # 销售药品对话框实现

├── SellMedicineDialog.h      # 销售药品对话框定义

├── StatisticsDialog.cpp      # 统计对话框实现

├── StatisticsDialog.h        # 统计对话框定义

├── yaopinguanli.cpp          # 主程序入口 (main函数)

└── yaopinguanli.pro          # Qt项目文件 (需要自行创建或使用CMake)


*(注意: `.pro` 文件未在提供的代码中，但对于qmake构建是必需的。或者可以使用CMake等其他构建系统。)*

## 如何编译与运行

### 前提条件

* 已安装 C++ 编译器 (支持 C++17，因为用到了 `std::filesystem`)，如 GCC, Clang, MSVC。
* 已安装 Qt 开发环境 (Qt 5.12 或更高版本，或 Qt 6) 并正确配置。

### 编译步骤 (以 Qt Creator 和 qmake 为例)

1.  **创建项目文件 (如果不存在):**
    如果项目中没有 `.pro` 文件，你需要在 Qt Creator 中创建一个新的 "Qt Widgets Application" 项目，然后将提供的所有 `.h` 和 `.cpp` 文件添加到该项目中。
    一个基础的 `.pro` 文件可能如下所示：
    ```pro
    QT       += core gui widgets
    TARGET = yaopinguanli
    TEMPLATE = app

    # C++17 for std::filesystem
    CONFIG += c++17

    SOURCES += \
        AddMedicineDialog.cpp \
        Database.cpp \
        Medicine.cpp \
        PharmacySystem.cpp \
        SellMedicineDialog.cpp \
        StatisticsDialog.cpp \
        yaopinguanli.cpp

    HEADERS += \
        AddMedicineDialog.h \
        Database.h \
        Medicine.h \
        PharmacySystem.h \
        SellMedicineDialog.h \
        StatisticsDialog.h
    ```
2.  **打开项目:** 使用 Qt Creator 打开项目文件 (`.pro` 或 `CMakeLists.txt`)。
3.  **配置构建套件 (Kit):** 确保选择了正确的编译器和 Qt 版本。
4.  **构建项目:** 点击 Qt Creator 左下角的构建图标 (锤子) 或按 `Ctrl+B` (Windows/Linux) / `Cmd+B` (macOS)。
5.  **运行项目:** 点击 Qt Creator 左下角的运行图标 (绿色三角形) 或按 `Ctrl+R` (Windows/Linux) / `Cmd+R` (macOS)。

### 数据文件路径

程序在 `Database.h` 中定义了数据文件的存储路径。原始代码中硬编码了一个绝对路径：
`dataDir = "E:/cpp_code/yaopinguanli_project/data";`

**重要提示:**
为了使程序能在不同环境下正常运行，建议修改此路径。程序已包含使用 `std::filesystem::create_directories(dataDir)` 创建目录的逻辑。
* **推荐修改方案 (相对路径):**
    在 `Database.h` 的构造函数中，将 `dataDir` 的赋值修改为：
    ```cpp
    dataDir = "data"; // 数据文件将存储在可执行文件同级目录下的 "data" 文件夹中
    ```
    或者，如果希望更精确地定位到应用数据目录（尤其是在macOS上，应用可能在bundle中运行）：
    ```cpp
    #include <QCoreApplication> // 如果尚未包含
    // ...
    dataDir = (QCoreApplication::applicationDirPath() + "/data").toStdString();
    ```
    确保程序有权限在选定的路径下创建目录和文件。

## 未来可改进方向

* **数据库升级:** 使用更健壮的数据库系统（如 SQLite）替代文本文件存储，以提高数据处理效率、查询能力和数据完整性。
* **用户认证与权限:** 增加用户登录机制和不同用户角色的权限管理。
* **高级报表与可视化:** 提供更多维度的销售分析，并引入图表展示（如条形图、折线图）。
* **库存预警机制:** 实现对药品库存量过低或药品临近保质期的自动提醒功能。
* **UI/UX 优化:** 改进界面设计，使其更加美观和用户友好，优化操作流程。
* **国际化支持:** 使程序能够支持多种语言。
* **全面的错误处理与日志记录:** 增强错误捕获机制，并提供更完善的日志系统以便于调试和追踪问题。
* **自动化测试:** 编写单元测试和集成测试用例，确保代码质量和系统稳定性。
* **配置文件管理:** 将如数据目录等可配置项移至外部配置文件，而不是硬编码在代码中。

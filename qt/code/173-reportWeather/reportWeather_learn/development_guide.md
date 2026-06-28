# ReportWeather 天气预报项目 — 逐步开发文档

## 目录

1. [项目概述](#1-项目概述)
2. [开发环境准备](#2-开发环境准备)
3. [分步开发步骤](#3-分步开发步骤)
4. [关键类解析](#4-关键类解析)
5. [关键方法详解](#5-关键方法详解)
6. [API 接口说明](#6-api-接口说明)
7. [UI 界面布局](#7-ui-界面布局)
8. [常见问题与调试技巧](#8-常见问题与调试技巧)

---

## 1. 项目概述

ReportWeather 是一个基于 **Qt 5 (Widget)** + **网络 API** 的天气预报桌面应用。主要功能包括：

- 根据城市名称查询未来 **6 天**的天气预报
- 显示当前温度、天气类型、风向风力、PM2.5、湿度、空气质量
- 以 **折线图** 形式展示每日最高温和最低温趋势
- 支持 **搜索城市** 切换天气数据
- 无边框窗口、右键菜单退出

### 核心技术栈

| 技术 | 用途 |
|------|------|
| Qt 5 Widgets | 界面布局与控件 |
| QNetworkAccessManager | 发起 HTTP 网络请求 |
| QJsonDocument / QJsonArray / QJsonObject | 解析 JSON 数据 |
| QPainter | 自定义绘制温度折线图 |
| QSS (Qt Style Sheets) | 控件样式美化 |

### 天气 API

- 服务商：易客天气（yiketianqi.com）
- API 版本：v9
- 请求方式：HTTP GET
- 返回格式：JSON

---

## 2. 开发环境准备

### 2.1 安装 Qt

**Windows 环境：**
- 下载 [Qt 5.14 或 5.15](https://download.qt.io/)
- 安装时勾选：
  - `MSVC 2019 64-bit` 或 `MinGW 7.3 64-bit`
  - `Qt Charts`（本项目中未使用，但为可选）
  - `Qt Network` 模块

**Linux 环境（Ubuntu）：**
```bash
sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt install libqt5network5  # 网络模块
```

### 2.2 Qt Creator 配置

1. 打开 Qt Creator
2. **Tools -> Options -> Kits** 确认编译器有效
3. 打开 `.pro` 文件即自动加载项目

### 2.3 新建项目（从头开始）

也可以在 Qt Creator 中：

1. **File -> New File or Project -> Application -> Qt Widgets Application**
2. 项目名称：`reportWeather`
3. **Kit Selection**：选择已安装的编译器
4. 取消勾选 `Generate form`（因为我们会手动添加 `.ui`）
5. 在 `.pro` 文件中添加 `QT += network`

> 本项目已生成完整的可编译源码，可直接打开 `.pro` 文件运行。

---

## 3. 分步开发步骤

### 第 1 步：创建基础项目结构

**目标**：建立 `.pro` 项目文件，配置模块依赖。

**核心文件**：`reportWeather.pro`

```pro
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    citycodeutils.cpp \
    day.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    citycodeutils.h \
    day.h \
    widget.h

FORMS += \
    widget.ui

RESOURCES += \
    citycode.qrc \
    res.qrc
```

**解析**：
- `QT += network` -- 启用网络模块，否则 `QNetworkAccessManager` 无法使用
- `FORMS += widget.ui` -- 指定 Qt Designer 生成的 UI 文件
- `RESOURCES` -- 注册资源文件（图片、JSON 数据）

**验证**：此时项目应能在 Qt Creator 中加载（但还不能编译通过，因为源码未就绪）。

---

### 第 2 步：创建入口文件 main.cpp

**目标**：应用程序入口，创建 QApplication 并显示主窗口。

**文件**：`main.cpp`

```cpp
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
```

**解析**：
- `QApplication a(argc, argv)` -- 每个 Qt 程序有且只有一个 QApplication 对象
- `w.show()` -- 显示窗口（默认是隐藏的）
- `a.exec()` -- 进入事件循环，程序在此等待用户操作

---

### 第 3 步：创建天气数据结构 Day 类

**目标**：定义存储单日天气数据的纯数据结构。

**文件**：`day.h`

```cpp
#ifndef DAY_H
#define DAY_H

#include <QString>

class Day
{
public:
    Day();

    QString mDate;       // 日期，如 "2024-01-24"
    QString mWeek;       // 星期，如 "星期三"
    QString mCity;       // 城市名
    QString mTemp;       // 当前温度
    QString mWeathType;  // 天气类型，如 "晴"、"多云"
    QString mTempLow;    // 最低温
    QString mTempHigh;   // 最高温
    QString mTips;       // 感冒指数等提示
    QString mFx;         // 风向
    QString mFl;         // 风力等级
    QString mPm25;       // PM2.5 指数
    QString mHu;         // 湿度
    QString mAirq;       // 空气质量等级（优/良/轻度等）
};

#endif // DAY_H
```

**关键说明**：
- 所有成员都是 `QString`，因为数据从 JSON 解析而来，直接存储字符串避免类型转换
- 这是一个 POD 类（Plain Old Data），没有复杂逻辑

---

### 第 4 步：创建城市编码查询工具 CityCodeUtils

**目标**：根据城市名称（如"深圳"）查询对应 API 城市编码（如"101280601"）。

**文件**：`citycodeutils.h`

```cpp
#ifndef CITYCODEUTILS_H
#define CITYCODEUTILS_H

#include <QMap>
#include <QString>

class CityCodeUtils
{
public:
    CityCodeUtils();
    QMap<QString,QString> cityMap = {};
    QString getCityCodeFromName(QString cityName);
    void initCityMap();
};

#endif // CITYCODEUTILS_H
```

**文件**：`citycodeutils.cpp`

```cpp
#include "citycodeutils.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

CityCodeUtils::CityCodeUtils() {}

QString CityCodeUtils::getCityCodeFromName(QString cityName)
{
    if(cityMap.isEmpty()){
        initCityMap();   // 第一次调用时延迟加载
    }

    QMap<QString, QString>::iterator it = cityMap.find(cityName);

    if( it == cityMap.end()){
        // 模糊匹配：尝试加上 "市"、"县"、"区"
        it = cityMap.find(cityName+"市");
        if(it == cityMap.end()) it = cityMap.find(cityName+"县");
        if(it == cityMap.end()) it = cityMap.find(cityName+"区");
        if(it == cityMap.end()) return "";  // 未找到
    }
    return it.value();
}

void CityCodeUtils::initCityMap()
{
    QFile file(":/citycode.json");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if(jsonDoc.isArray()){
        QJsonArray citys = jsonDoc.array();
        for(QJsonValue value : citys){
            if(value.isObject()){
                QString cityName = value["city_name"].toString();
                QString cityCode = value["city_code"].toString();
                cityMap.insert(cityName, cityCode);
            }
        }
    }
}
```

**方法解析**：

| 方法 | 功能 | 关键细节 |
|------|------|----------|
| `initCityMap()` | 从 JSON 文件加载城市映射表 | 使用 `QFile` 读取资源文件 `:/citycode.json`；JSON 是一个数组，每个元素含 `city_name` 和 `city_code` |
| `getCityCodeFromName()` | 根据名称查找城市编码 | 先精确查找，失败后尝试加"市/县/区"后缀模糊查找 |

**城市编码 JSON 数据结构**：
```json
[
  {
    "id": 1,
    "pid": 0,
    "city_code": "101010100",
    "city_name": "北京",
    "post_code": "100000",
    "area_code": "010"
  },
  ...
]
```

---

### 第 5 步：设计 UI 界面

**目标**：使用 Qt Designer（或直接编写 XML）创建完整的界面布局。本项目使用 `widget.ui` 文件。

**整体布局**（垂直布局，4 个主要区域）：

```
+-------------------------------------------+
|  widget01: [搜索框] [搜索按钮]   日期        |  <- 顶部功能区
+-------------------------------------------+
|  widget02: [天气图标] 温度/城市              |  <- 当前天气主显区
|              天气类型/温度范围               |
+-------------------------------------------+
|  widget03: [温馨提示]                       |  <- 详细信息区
|   风向 | PM2.5 | 空气质量 | 湿度             |
+-------------------------------------------+
|  widget04: 6 天预报                        |  <- 预报数据区
|   星期/日期 | 天气图标/类型                  |
|   空气质量 | 最高温折线图                    |
|   最低温折线图 | 风向/风力                   |
+-------------------------------------------+
```

**UI 设计要点**：

1. **widget01（顶部）**：
   - `QLineEdit` -- 城市输入框，支持回车搜索
   - `QPushButton` -- 搜索按钮（放大镜图标）
   - `QLabel(labelCurrentDate)` -- 当前日期显示

2. **widget02（当前天气）**：
   - `QLabel(labelWeatherIcon)` -- 天气类型大图标
   - `QLabel(labelTmp)` -- 当前温度（大号字体 37pt）
   - `QLabel(labelCity)` -- 城市名称
   - `QLabel(labelweatherType)` -- 天气描述（晴/多云等）
   - `QLabel(labelTempRange)` -- 温度范围（最低温~最高温）

3. **widget03（详细信息）**：
   - `QLabel(labelGaomao)` -- 感冒指数等温馨提示
   - 4 个信息卡片（圆角橙色背景）：
     - 风向 + 风力
     - PM2.5 数值
     - 空气质量等级
     - 湿度百分比

4. **widget04（6 天预报）**：
   - `widget0401` -- 星期标签（6 列：今天/明天/后天... + 日期）
   - `widget0402` -- 天气图标 + 天气类型
   - `widget0403` -- 空气质量标签（按等级着色）
   - `widget0404` -- 最高温折线图（QPainter 自定义绘制）
   - `widget0405` -- 最低温折线图（QPainter 自定义绘制）
   - `widget0406` -- 风向 + 风力

**设置无边框窗口**：
```cpp
setWindowFlag(Qt::FramelessWindowHint);
```

**实现窗口拖拽**：
```cpp
// 鼠标按下时记录偏移量
void Widget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
        mOffset = event->globalPos() - this->pos();
}

// 鼠标移动时重新定位窗口
void Widget::mouseMoveEvent(QMouseEvent *event) {
    this->move(event->globalPos() - mOffset);
}
```

**右键退出菜单**：
```cpp
menuQuit = new QMenu(this);
menuQuit->setStyleSheet("QMenu::item {color:white}");
QAction *closeAct = new QAction(QIcon(":/res/close.png"), tr("退出"), this);
menuQuit->addAction(closeAct);
connect(menuQuit, &QMenu::triggered, this, [=]{ this->close(); });
```

---

### 第 6 步：网络请求与 JSON 解析

**目标**：发起 HTTP GET 请求获取天气数据，解析 JSON 并更新 UI。

#### 6.1 初始化网络管理器

在 `Widget` 构造函数中：

```cpp
manager = new QNetworkAccessManager(this);
strUrl = "http://v1.yiketianqi.com/api?unescape=1&version=v9&appid=26371314&appsecret=qOhoD413";
QUrl urlTianQi(strUrl);
QNetworkRequest res(urlTianQi);
reply = manager->get(res);

connect(manager, &QNetworkAccessManager::finished, this, &Widget::readHttpRply);
```

**解析**：
- `QNetworkAccessManager` -- Qt 网络访问的核心类
- `manager->get()` -- 发起 GET 请求，返回 `QNetworkReply*`
- 信号 `finished` 在请求完成时触发

#### 6.2 读取网络回复

```cpp
void Widget::readHttpRply(QNetworkReply *reply)
{
    int resCode = reply->attribute(
        QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error() == QNetworkReply::NoError && resCode == 200){
        QByteArray data = reply->readAll();
        parseWeatherJsonDataNew(data);  // 解析 JSON
    } else {
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("网络请求失败");
        mes.exec();
    }
}
```

注意：先检查 `reply->error()` 再检查 HTTP 状态码，避免网络错误时崩溃。

#### 6.3 JSON 数据解析

**API v9 返回的 JSON 结构**：
```json
{
  "city": "深圳",
  "aqi": { "pm25": "24" },
  "data": [
    {
      "date": "2024-01-24",
      "week": "星期三",
      "wea": "晴",
      "tem": "23℃",
      "tem1": "26",
      "tem2": "20",
      "win": ["东南风"],
      "win_speed": "2级",
      "air_level": "优",
      "humidity": "65%",
      "index": [
        {}, {}, {},
        { "desc": "各类人群可自由活动" }
      ]
    }
  ]
}
```

**解析代码**：
```cpp
void Widget::parseWeatherJsonDataNew(QByteArray rawData)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if(!jsonDoc.isNull() && jsonDoc.isObject()){
        QJsonObject jsonRoot = jsonDoc.object();

        // 解析城市和 PM2.5（在根对象中）
        days[0].mCity = jsonRoot["city"].toString();
        days[0].mPm25 = jsonRoot["aqi"].toObject()["pm25"].toString();

        if(jsonRoot.contains("data") && jsonRoot["data"].isArray()){
            QJsonArray weaArray = jsonRoot["data"].toArray();
            for(int i = 0; i < weaArray.size(); i++){
                QJsonObject obj = weaArray[i].toObject();
                days[i].mDate = obj["date"].toString();
                days[i].mWeek = obj["week"].toString();
                days[i].mWeathType = obj["wea"].toString();
                days[i].mTemp = obj["tem"].toString();
                days[i].mTempLow = obj["tem2"].toString();
                days[i].mTempHigh = obj["tem1"].toString();
                days[i].mFx = obj["win"].toArray()[0].toString();
                days[i].mFl = obj["win_speed"].toString();
                days[i].mAirq = obj["air_level"].toString();
                days[i].mHu = obj["humidity"].toString();
                days[i].mTips = obj["index"].toArray()[3]
                                    .toObject()["desc"].toString();
            }
        }
    }
    updateUI();
}
```

**关键方法**：

| 方法 | 说明 |
|------|------|
| `QJsonDocument::fromJson()` | 将 JSON 字符串解析为文档对象 |
| `jsonDoc.isObject()` | 判断是否为 JSON 对象 |
| `jsonRoot["key"].toString()` | 获取指定 key 的字符串值 |
| `jsonRoot["aqi"].toObject()` | 获取嵌套对象 |
| `obj["win"].toArray()[0]` | 获取数组的第一个元素 |
| `obj["index"].toArray()[3]` | 获取第 4 个指数信息 |

---

### 第 7 步：更新 UI 界面

**目标**：将解析后的数据填充到各个控件中。

```cpp
void Widget::updateUI()
{
    // 当前天气信息
    ui->labelCurrentDate->setText(days[0].mDate + "  " + days[0].mWeek);
    ui->labelCity->setText(days[0].mCity + "市");
    ui->labelTmp->setText(days[0].mTemp + "℃");
    ui->labelTempRange->setText(days[0].mTempLow + "℃~" + days[0].mTempHigh + "℃");
    ui->labelweatherType->setText(days[0].mWeathType);
    ui->labelWeatherIcon->setPixmap(mTypeMap[days[0].mWeathType]);
    ui->labelGaomao->setText(days[0].mTips);
    ui->labelFXType->setText(days[0].mFx);
    ui->labelFXType_2->setText(days[0].mFl);
    ui->labelPM25Data->setText(days[0].mPm25);
    ui->labelShiduData->setText(days[0].mHu);
    ui->labelairData->setText(days[0].mAirq);

    // 6 天预报循环
    for(int i = 0; i < 6; i++){
        mWeekList[i]->setText(days[i].mWeek);
        mWeekList[0]->setText("今天");
        mWeekList[1]->setText("明天");
        mWeekList[2]->setText("后天");

        QStringList dayList = days[i].mDate.split("-");
        mDateList[i]->setText(dayList.at(1) + "-" + dayList.at(2));

        // 天气图标（处理 "小雨转多云" 复合类型）
        int index = days[i].mWeathType.indexOf("转");
        QPixmap pixmap;
        if(index != -1){
            pixmap = mTypeMap[days[i].mWeathType.left(index)];
        } else {
            pixmap = mTypeMap[days[i].mWeathType];
        }
        pixmap = pixmap.scaled(mIconList[i]->size(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mIconList[i]->setPixmap(pixmap);

        mWeaTypeList[i]->setText(days[i].mWeathType);

        // 空气质量着色
        QString airQ = days[i].mAirq;
        mAirqList[i]->setText(airQ);
        if(airQ == "优")   mAirqList[i]->setStyleSheet(
            "background-color: rgb(150, 213, 32); border-radius: 7px;");
        if(airQ == "良")   mAirqList[i]->setStyleSheet(
            "background-color: rgb(208, 107, 39); border-radius: 7px;");
        if(airQ == "重度") mAirqList[i]->setStyleSheet(
            "background-color: rgb(153, 0, 0); border-radius: 7px;");
        // ...
    }
    update();
}
```

**控件列表绑定**：
```cpp
mWeekList << ui->labelday0 << ui->labelday1 << ui->labelday2
          << ui->labelday3 << ui->labelday4 << ui->labelday5;
mDateList << ui->labelDate0 << ui->labelDate1 << ui->labelDate2
          << ui->labelDate3 << ui->labelDate4 << ui->labelDate5;
// ... 类似绑定 mIconList, mWeaTypeList, mAirqList, mFxList, mFlList
```

---

### 第 8 步：绘制温度折线图

**目标**：使用 QPainter 在 `widget0404` 和 `widget0405` 上绘制最高温和最低温的折线图。

**核心原理**：
- 使用事件过滤器 `eventFilter` 拦截 `QEvent::Paint`，在 QWidget 绘制时自定义绘图
- 计算 6 天的温度平均值，以平均温度为基准线
- 每个点通过 `(温度值 - 平均值) * 系数` 计算偏移量

```cpp
void Widget::drawTempLineHigh()
{
    QPainter painter(ui->widget0404);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::yellow);

    int sum = 0;
    int offSet = 0;
    int middle = ui->widget0404->height() * 0.7;
    for(int i = 0; i < 6; i++) sum += days[i].mTempHigh.toInt();
    int ave = sum / 6;

    QPoint points[6];
    for(int i = 0; i < 6; i++){
        points[i].setX(mAirqList[i]->x() + mAirqList[i]->width() / 2);
        offSet = (days[i].mTempHigh.toInt() - ave) * 2;
        points[i].setY(middle - offSet);
        painter.drawEllipse(QPoint(points[i]), 3, 3);
        painter.drawText(points[i].x() - 15, points[i].y() - 15,
                         days[i].mTempHigh + "°");
    }
    for(int i = 0; i < 5; i++)
        painter.drawLine(points[i], points[i + 1]);
}
```

**最低温绘制**逻辑相同，只是颜色不同（青色 `QColor(70, 192, 203)`）。

**事件过滤器注册**：
```cpp
ui->widget0404->installEventFilter(this);
ui->widget0405->installEventFilter(this);

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widget0404 && event->type() == QEvent::Paint){
        drawTempLineHigh();
        return true;
    }
    if(watched == ui->widget0405 && event->type() == QEvent::Paint){
        drawTempLineLow();
        return true;
    }
    return QWidget::eventFilter(watched, event);
}
```

> 为什么用事件过滤器：因为 `widget0404` 和 `widget0405` 是 UI 文件中的普通 QWidget，无法直接重写其 `paintEvent`。事件过滤器让我们能在不创建子类的情况下拦截绘制事件。

---

### 第 9 步：城市搜索切换

**目标**：用户输入城市名，查找城市编码，重新请求天气数据。

```cpp
void Widget::on_pushButton_clicked()
{
    QString cityNameFromUser = ui->lineEditCity->text();
    QString cityCode = cityCodeUtils.getCityCodeFromName(cityNameFromUser);
    if(cityCode != NULL){
        strUrl += "&cityid=" + cityCode;
        manager->get(QNetworkRequest(QUrl(strUrl)));
    } else {
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("请输入正确的城市名");
        mes.exec();
    }
}

// 回车键等同于点击搜索按钮
void Widget::on_lineEditCity_returnPressed()
{
    on_pushButton_clicked();
}
```

---

## 4. 关键类解析

### 4.1 Day 类

| 成员 | 类型 | 说明 | JSON 来源 |
|------|------|------|-----------|
| `mDate` | QString | 日期 | `data[i].date` |
| `mWeek` | QString | 星期 | `data[i].week` |
| `mCity` | QString | 城市名 | `city`（根对象） |
| `mTemp` | QString | 当前温度 | `data[i].tem` |
| `mWeathType` | QString | 天气类型 | `data[i].wea` |
| `mTempLow` | QString | 最低温 | `data[i].tem2` |
| `mTempHigh` | QString | 最高温 | `data[i].tem1` |
| `mTips` | QString | 生活提示 | `data[i].index[3].desc` |
| `mFx` | QString | 风向 | `data[i].win[0]` |
| `mFl` | QString | 风力 | `data[i].win_speed` |
| `mPm25` | QString | PM2.5 | `aqi.pm25`（根对象） |
| `mHu` | QString | 湿度 | `data[i].humidity` |
| `mAirq` | QString | 空气质量 | `data[i].air_level` |

### 4.2 CityCodeUtils 类

| 方法 | 功能 | 时间复杂度 |
|------|------|------------|
| `initCityMap()` | 从 JSON 加载城市编码映射表 | O(n) |
| `getCityCodeFromName()` | 按名称查编码（支持模糊匹配） | O(log n) |

### 4.3 Widget 类（核心）

**成员变量**：

| 变量 | 类型 | 用途 |
|------|------|------|
| `days[7]` | Day[] | 存储 7 天天气数据 |
| `mDateList / mWeekList / ...` | QList<QLabel*> | 控件指针列表 |
| `mTypeMap` | QMap<QString,QString> | 天气类型到图标路径的映射 |
| `manager` | QNetworkAccessManager* | 网络请求管理器 |
| `reply` | QNetworkReply* | 网络回复对象 |
| `strUrl` | QString | API 请求地址 |
| `menuQuit` | QMenu* | 右键退出菜单 |
| `mOffset` | QPoint | 窗口拖拽偏移量 |

**核心方法调用链**：

```
构造函数
  +-- 设置 UI、无边框窗口、右键菜单
  +-- 初始化网络管理器 --> 发起天气 API 请求
  +-- 绑定控件列表和天气类型图标映射

网络请求完成
  +-- readHttpRply()
       +-- parseWeatherJsonDataNew()
            +-- updateUI()
                 +-- 填充当前天气控件
                 +-- 循环填充 6 天预报控件
                 +-- update() 触发重绘 --> 折线图

用户搜索城市
  +-- on_pushButton_clicked()
  |    +-- getCityCodeFromName() --> 查编码
  |    +-- manager->get() --> 新请求
  +-- on_lineEditCity_returnPressed() --> 同上
```

---

## 5. 关键方法详解

### 5.1 parseWeatherJsonDataNew

**功能**：解析 API v9 返回的 JSON 数据，填充 `days[]` 数组。

**解析要点**：
1. 先检查 `jsonDoc.isNull()` 防止空数据崩溃
2. 使用 `jsonDoc.isObject()` 确保根节点是对象
3. 城市和 PM2.5 在根对象中，其他在 `data` 数组中
4. 风向 `win` 是数组，取 `[0]`；提示信息在 `index[3].desc`

### 5.2 updateUI

**功能**：将所有解析后的数据显示到界面控件。

**要点**：
- "今天"/"明天"/"后天" 手动设置前 3 天的星期标签
- 日期从 `"2024-01-24"` 格式截取为 `"01-24"`
- 天气类型含"转"字时（如"小雨转多云"），取前半段显示图标
- 空气质量用不同背景色区分等级
- 调用 `update()` 触发重绘

### 5.3 drawTempLineHigh / drawTempLineLow

**功能**：绘制最高温/最低温的折线图。

**算法**：
1. 计算 6 天温度的平均值
2. 以 widget 高度的 70% 为基准线
3. 每个点的 Y 偏移 = `(温度值 - 平均值) * 系数`（高温系数 2，低温系数 3）
4. 用 `drawEllipse` 画圆点，`drawText` 标温度，`drawLine` 连线

### 5.4 eventFilter

**功能**：拦截绘制事件，在指定 widget 上绘制折线图。

为什么用 eventFilter：widget0404/0405 是在 `.ui` 中定义的普通 QWidget，无法通过继承重写 `paintEvent`。事件过滤器提供了非侵入式的自定义绘制方案。

### 5.5 mousePressEvent / mouseMoveEvent

**功能**：实现无边框窗口的拖拽移动。

**原理**：
- 鼠标按下时记录窗口左上角到点击位置的偏移量
- 鼠标移动时将窗口重新定位到 `(鼠标全局位置 - 偏移量)`

### 5.6 readHttpRply

**功能**：处理网络请求完成后的回调。

**安全检查**：
- `reply->error() == QNetworkReply::NoError` -- 确认无网络错误
- HTTP 状态码 200 -- 确认服务器正常响应
- 任一条件不满足则弹出错误提示框

---

## 6. API 接口说明

### 6.1 易客天气 API v9

**请求地址**：
```
http://v1.yiketianqi.com/api?unescape=1&version=v9&appid=26371314&appsecret=qOhoD413
```

**参数说明**：

| 参数 | 说明 |
|------|------|
| `unescape=1` | 不转义中文字符 |
| `version=v9` | API 版本号 |
| `appid` | 应用 ID |
| `appsecret` | 密钥 |
| `cityid` | （可选）城市编码，用于切换城市 |

### 6.2 城市编码数据

城市编码来源于 `citycode.json`，格式为：
```json
[{ "city_name": "深圳", "city_code": "101280601" }, ...]
```

---

## 7. UI 界面布局

### 7.1 整体规格

- 窗口尺寸：`507 x 945`
- 背景色：深灰 `rgb(22, 22, 22)`
- 字体色：浅灰 `rgb(230, 230, 230)`
- 无边框、无标题栏

### 7.2 控件命名约定

| 前缀 | 含义 | 示例 |
|------|------|------|
| `label` | 数据显示标签 | `labelTmp`, `labelCity` |
| `widget` | 容器 | `widget01`, `widget02` |
| `pushButton` | 按钮 | `pushButton` |
| `lineEdit` | 输入框 | `lineEditCity` |

### 7.3 6 天预报的控件索引规则

第 i 天的预报使用后缀 `i` 的控件名：

| 控件名 | 含义 |
|--------|------|
| `labelday0` ~ `labelday5` | 星期 |
| `labelDate0` ~ `labelDate5` | 日期 |
| `labelWheatherIcon0` ~ `labelWheatherIcon5` | 天气图标 |
| `lbweatherTypeDate0` ~ `lbweatherTypeDate5` | 天气类型 |
| `labelaiq0` ~ `labelaiq5` | 空气质量 |
| `labelFX0` ~ `labelFX5` | 风向 |
| `labelFL0` ~ `labelFL5` | 风力 |

---

## 8. 常见问题与调试技巧

### 8.1 编译报错

| 错误 | 原因 | 解决 |
|------|------|------|
| `undefined reference to QNetworkAccessManager` | 未链接网络模块 | 在 `.pro` 中添加 `QT += network` |
| `citycode.json: No such file` | 资源文件未注册 | 确保 `citycode.qrc` 已创建且内容正确 |
| `ui_widget.h: No such file` | 未生成 UI 头文件 | 运行 `qmake` 重新生成 |
| `Cannot find type QPainter` | 缺少头文件 | 添加 `#include <QPainter>` |

### 8.2 网络请求失败

- 检查网络连接：可否正常访问网页
- 检查 API URL：确保 `appid` 和 `appsecret` 有效
- 查看状态码：在 `readHttpRply` 中打印 `resCode`
- 启用调试输出：`qDebug() << QString::fromUtf8(data);`

### 8.3 JSON 解析为空

- 调用 `QJsonParseError` 获取错误信息：
  ```cpp
  QJsonParseError err;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData, &err);
  qDebug() << err.errorString();
  ```
- 检查 API 返回是否为正确的 JSON 格式

### 8.4 折线图不显示

- 确认已调用 `installEventFilter()`
- 确认 `eventFilter()` 返回 `true`
- 检查 `days[]` 数组是否有有效数据
- 尝试在 `drawTempLineHigh()` 中加入 `qDebug()` 打印坐标值

### 8.5 窗口无法拖拽

- 确认 `setWindowFlag(Qt::FramelessWindowHint)` 已设置
- 检查 `mousePressEvent` 和 `mouseMoveEvent` 是否正确实现

---

## 附录：完整开发路线图

建议按以下顺序逐步完成：

| 步骤 | 任务 | 预计耗时 |
|------|------|----------|
| 1 | 创建项目文件和目录结构 | 10min |
| 2 | 编写 main.cpp | 5min |
| 3 | 编写 Day 数据类 | 10min |
| 4 | 编写 CityCodeUtils 城市编码工具 | 20min |
| 5 | 设计 UI 界面（widget.ui） | 60min |
| 6 | 搭建 Widget 框架 + 网络请求 | 30min |
| 7 | JSON 解析 + UI 更新 | 40min |
| 8 | 温度折线图绘制 | 30min |
| 9 | 城市搜索功能 | 15min |
| 10 | 调试和优化 | 30min |

**总预计耗时**：约 3.5 小时

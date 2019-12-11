// -*- C++ -*-
/*!
 * @file  RGBXYZPointCloudViewerTest.cpp
 * @brief RGBXYZ Point Cloud Viewer
 * @date $Date$
 *
 * $Id$
 */

#include "RGBXYZPointCloudViewerTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rgbxyzpointcloudviewer_spec[] =
  {
    "implementation_id", "RGBXYZPointCloudViewerTest",
    "type_name",         "RGBXYZPointCloudViewerTest",
    "description",       "RGBXYZ Point Cloud Viewer",
    "version",           "1.0.0",
    "vendor",            "Masayuki Fukao, Robot System Design Laboratory, Meijo University",
    "category",          "Pointcloud",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RGBXYZPointCloudViewerTest::RGBXYZPointCloudViewerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InPointCloudIn("InPointCloud", m_InPointCloud)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RGBXYZPointCloudViewerTest::~RGBXYZPointCloudViewerTest()
{
}



RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("InPointCloud", m_InPointCloudOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBXYZPointCloudViewerTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RGBXYZPointCloudViewerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(rgbxyzpointcloudviewer_spec);
    manager->registerFactory(profile,
                             RTC::Create<RGBXYZPointCloudViewerTest>,
                             RTC::Delete<RGBXYZPointCloudViewerTest>);
  }
  
};



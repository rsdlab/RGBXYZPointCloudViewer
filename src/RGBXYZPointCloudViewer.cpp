// -*- C++ -*-
/*!
 * @file  RGBXYZPointCloudViewer.cpp
 * @brief RGBXYZ Point Cloud Viewer
 * @date $Date$
 *
 * $Id$
 */

#include "RGBXYZPointCloudViewer.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rgbxyzpointcloudviewer_spec[] =
  {
    "implementation_id", "RGBXYZPointCloudViewer",
    "type_name",         "RGBXYZPointCloudViewer",
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
RGBXYZPointCloudViewer::RGBXYZPointCloudViewer(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InPointCloudIn("InPointCloud", m_InPointCloud)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RGBXYZPointCloudViewer::~RGBXYZPointCloudViewer()
{
}



RTC::ReturnCode_t RGBXYZPointCloudViewer::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("InPointCloud", m_InPointCloudIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

RTC::ReturnCode_t RGBXYZPointCloudViewer::onActivated(RTC::UniqueId ec_id)
{
  m_InPointCloud.raw_XYZdata.length();
  m_InPointCloud.raw_RGBdata.length();
  //メモリの確保
  PCViewer.reset(new pcl::visualization::PCLVisualizer ("Point Cloud Viewer"));
  //ビューワーの背景の設定
  PCViewer->setBackgroundColor (0, 0, 0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RGBXYZPointCloudViewer::onDeactivated(RTC::UniqueId ec_id)
{
  //ビューワーを閉じる
  PCViewer->close();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RGBXYZPointCloudViewer::onExecute(RTC::UniqueId ec_id)
{
  //データポートが更新されているかの確認
  if(m_InPointCloudIn.isNew()){
    //データポートを読み込む
    m_InPointCloudIn.read();
    //データセット
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr PointCloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    PointCloud->width  = static_cast<uint32_t>( m_InPointCloud.width );   
    PointCloud->height = static_cast<uint32_t>( m_InPointCloud.height );
    PointCloud->is_dense = false;
    PointCloud->points.resize(m_InPointCloud.width * m_InPointCloud.height);
    
    //入力データをpclの方に格納
    float *src = (float *)m_InPointCloud.raw_XYZdata.get_buffer();
    uint8_t *src1 = (uint8_t *)m_InPointCloud.raw_RGBdata.get_buffer();
    for(int i = 0 ; i < m_InPointCloud.height ; i ++){
      for(int j = 0 ; j < m_InPointCloud.width ; j ++ ){
	int xyzrgbcounter = i * m_InPointCloud.width * 3 + j * 3 ;
	int xyzrgbcounter1 = i * m_InPointCloud.width + j ;

	PointCloud->points[ xyzrgbcounter1].x = src[xyzrgbcounter] ;
	PointCloud->points[ xyzrgbcounter1].y = src[xyzrgbcounter + 1] ;
	PointCloud->points[ xyzrgbcounter1].z = src[xyzrgbcounter + 2] ;
	PointCloud->points[ xyzrgbcounter1].r = src1[xyzrgbcounter] ;
	PointCloud->points[ xyzrgbcounter1].g = src1[xyzrgbcounter + 1] ;
	PointCloud->points[ xyzrgbcounter1].b = src1[xyzrgbcounter + 2] ;
      }
    }
    //ビューワーに点群データを反映させる
    PCViewer->addPointCloud<pcl::PointXYZRGB> (PointCloud, "Cloud");
    PCViewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud"); 
    PCViewer->spinOnce(10000,true);

    //.pcd形式で保存
    PCSaveFileName = "SavePC_" + std::to_string(count) + ".pcd";
    pcl::io::savePCDFileASCII(PCSaveFileName, *PointCloud); 
    printf("save finish : \n");
    count = count + 1;     
    PCViewer->removePointCloud("Cloud"); 
  }
 
  
  return RTC::RTC_OK;
}

extern "C"
{
 
  void RGBXYZPointCloudViewerInit(RTC::Manager* manager)
  {
    coil::Properties profile(rgbxyzpointcloudviewer_spec);
    manager->registerFactory(profile,
                             RTC::Create<RGBXYZPointCloudViewer>,
                             RTC::Delete<RGBXYZPointCloudViewer>);
  }
  
};



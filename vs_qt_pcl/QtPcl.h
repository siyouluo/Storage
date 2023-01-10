#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPcl.h"

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
#endif
 
#include <QFileDialog>
#include <vtkRenderWindow.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
 
class QtPcl : public QMainWindow
{
   Q_OBJECT
   
public:
    QtPcl(QWidget *parent = Q_NULLPTR);
 
private:
    Ui::QtPclClass ui;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    void initialVtkWidget();

    private slots :
        void onOpen();
};

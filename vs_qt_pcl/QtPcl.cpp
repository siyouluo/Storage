#include "QtPcl.h"

QtPcl::QtPcl(QWidget *parent)
    :QMainWindow(parent)
{
    ui.setupUi(this);
    initialVtkWidget();
    connect(ui.actionOpen,SIGNAL(triggered()), this, SLOT(onOpen()));
}

void QtPcl::initialVtkWidget()
{
      cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
      viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
      viewer->addPointCloud(cloud,"cloud");    
      ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
      viewer->setupInteractor(ui.qvtkWidget->GetInteractor(),ui.qvtkWidget->GetRenderWindow());    
      ui.qvtkWidget->update();  
}
void QtPcl::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open PointCloud", ".", "Open PCD files(*.pcd)");
    if (!fileName.isEmpty()){
        std::string file_name = fileName.toStdString();
        pcl::PCLPointCloud2 cloud2;
        Eigen::Vector4f origin;
        Eigen::Quaternionf orientation;
        int pcd_version;
        int data_type;
        unsigned int data_idx;
        int offset = 0;
        pcl::PCDReader rd;
        rd.readHeader(file_name,cloud2, origin, orientation, pcd_version, data_type, data_idx);
        if (data_type == 0)
        {
            pcl::io::loadPCDFile(fileName.toStdString(),*cloud);
        }    
        else if (data_type == 2)
        {          
            pcl::PCDReader reader;
            reader.read<pcl::PointXYZ>(fileName.toStdString(),*cloud);
        }
        viewer->updatePointCloud(cloud,"cloud");
        viewer->resetCamera();
        ui.qvtkWidget->update();
    }
}
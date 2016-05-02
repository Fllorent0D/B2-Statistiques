#include "graphstat2d.h"
#include "ui_graphstat2d.h"

GraphStat2D::GraphStat2D(const EtudeStat2D* E1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphStat2D)
{
   ui->setupUi(this);
   setMouseTracking(true);
   EtudeLocal = (EtudeStat2D*)E1;
   p = dynamic_cast<DataSourceSerie2D*>((EtudeLocal->getE())->getSource());
   
   //Calcul A et B
   //EtudeLocal->setAB();
   writeEquation();
   setMinMax();
// juste pour debuter

	
}

GraphStat2D::~GraphStat2D()
{
    delete ui;
}
void GraphStat2D::setMinMax()
{
  float tmp;
  MinX = p->getXi(0);
  MinY = p->getYi(0);
  MaxX = p->getXi(0);
  MaxY = p->getYi(0);

  for (int i = 1; i < p->getEffTotal(); ++i)
  {
    tmp = p->getXi(i);
    if(tmp < MinX)
      MinX = tmp;
    if(tmp > MaxX)
      MaxX = tmp;
    
    tmp = p->getYi(i);
    if(tmp < MinY)
      MinY = tmp;
    if(tmp > MaxY)
      MaxY = tmp;

  }
}
void GraphStat2D::findSelectedPoints()
{
  

}
void GraphStat2D::on_ButtonTracer_clicked()
{
    

    this->update();
}

void GraphStat2D::on_ButtonSelectionner_clicked()
{
	int x, y, pts = 0, bcl = p->getL()->Size();
  Data2D *pD2D;


  for(int i = 0; i < bcl; i++)
  {
    x = (80 + (p->getXi(i) - MinX)*340 / (MaxX-MinX)) ;
    y = (320 - (p->getYi(i) - MinY)*276 / (MaxY-MinY)) ;
    if(PointDepart.x() <= x && PointArrivee.x() >= x && PointDepart.y() <= y && PointArrivee.y() >= y)
    {
      pD2D = new Data2D(p->getXi(i), p->getYi(i));
      p->getL()->Suppression(*pD2D);
      LUndo.Ajout(*pD2D);
      pts++;
      delete pD2D;
    }
  }
  
  p->setEffTotal(p->getEffTotal() - pts);

  PointArrivee.setX(0);
  PointArrivee.setY(0);
  PointDepart.setX(0); 
  PointDepart.setY(0); 
  TracerCarre = false;

  EtudeLocal->setMoyenne1();
  EtudeLocal->setMoyenne2();
  EtudeLocal->setAB();
  writeEquation();
  setMinMax();
  this->update();

    
}
void GraphStat2D::writeEquation()
{
	char buff[50];
	sprintf(buff, "y = %.4fx + %.4f", EtudeLocal->getA(), EtudeLocal->getB());
    ui->lineEquation->setText(buff);

}

void GraphStat2D::on_ButtonAnnuler_clicked()
{
  if(!LUndo.vide())
  {
    Data2D pD2D;
    pD2D = LUndo.getElement(0);
    LUndo.Suppression(pD2D);
    p->getL()->Ajout(pD2D);
    p->setEffTotal(p->getEffTotal() + 1);

    setMinMax();
    EtudeLocal->setMoyenne1();
    EtudeLocal->setMoyenne2();
    EtudeLocal->setAB();
    writeEquation();
    setMinMax();
    //cout << *((EtudeLocal->getE())->getSource()) << endl;
       //ui->lineEquation->clear();
       this->update();    
  }


    
}

void GraphStat2D::paintEvent(QPaintEvent *)
{
	int x, y;
	int L1, C1, L2, C2;
    float x1, x2, y1, y2;
  QPen pen(Qt::darkGray);

	QPainter painter(this);
  
  painter.drawLine(50, 20, 50, 360);
  painter.drawLine(50, 360, 460, 360);
    
  char 	Buff[10];
	sprintf(Buff,"%-8.2f",MinY);
	painter.drawText(10 ,324,Buff);	
	sprintf(Buff,"%-8.2f",MaxY);
	painter.drawText(10 ,45,Buff);

	sprintf(Buff,"%-8.2f",MinX);
	painter.drawText(63 ,380,Buff);
	sprintf(Buff,"%-8.2f",MaxX);
	painter.drawText(394 ,380,Buff);

	if(TracerCarre)
	   painter.setPen(pen);   
  
  painter.drawRect(PointDepart.x(), PointDepart.y(), PointArrivee.x() - PointDepart.x(), PointArrivee.y() - PointDepart.y());
  pen.setBrush(Qt::black);
  painter.setPen(pen);
	for (int i = 0; i < p->getEffTotal(); ++i)
    {
    	x = (80 + (p->getXi(i) - MinX)*340 / (MaxX-MinX)) -3;
    	y = (320 - (p->getYi(i) - MinY)*276 / (MaxY-MinY)) +3;

        painter.drawText(x , y , "X");
    }
    
    /* Tracer la droite test*/
    x1 = MinX;
    y1 = EtudeLocal->Xi(x1);
    x2 = MaxX;
    y2 = EtudeLocal->Xi(x2);

    L1 = (80 + (x1 - MinX) * 340 / (MaxX-MinX)) - 3 ;
    C1 = (320 - (((y1 - MinY) * 276 / (MaxY-MinY)) )) + 3;
    
    L2 = (80+ (x2 - MinX) * 340 / (MaxX-MinX))  -3;
    C2 = (320 - ((y2 - MinY) * 276 / (MaxY-MinY) )) +3;    
    
    painter.drawLine(L1, C1,L2,C2 );


}
void GraphStat2D::mouseMoveEvent(QMouseEvent *e)
{
  if(TracerCarre)
  {
  PointArrivee = e->pos();
  this->update();
    
  }
}
void GraphStat2D::mouseReleaseEvent(QMouseEvent * e)
{
	
   PointArrivee = e->pos();
   TracerCarre = false;
   QPoint tmp;

   if(PointArrivee.x() < PointDepart.x() && PointArrivee.y() < PointDepart.y())
   {
   		tmp = PointDepart;
   		PointDepart = PointArrivee;
   		PointArrivee = tmp;
   }
   else if(PointDepart.x() > PointArrivee.x() && PointDepart.y() < PointArrivee.y())
   {
      tmp = PointDepart;
      PointDepart.setX(PointArrivee.x());
      PointArrivee.setX(tmp.x());
   }
   else if (PointDepart.x() < PointArrivee.x() && PointDepart.y() > PointArrivee.y())
   {
      tmp = PointDepart;
      PointDepart.setY(PointArrivee.y());
      PointArrivee.setY(tmp.y());
   }

   findSelectedPoints();
   this->update();
}

void GraphStat2D::mousePressEvent(QMouseEvent * e)
{
	PointDepart = e->pos();
	TracerCarre = true; 
  	//this->update();
}


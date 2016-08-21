/********************************************//**
 * \brief Link between blocks
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/

#include "Link.h"
#include "Desk.h"

using namespace std;
using namespace nana;
Link::Link(Desk* dk,int blockid,int outportid):drawing(*dk)
{
    dsk=dk;
    id=dsk->linkset.size();
    B1=blockid;
    P1=outportid;
    lcolor=colors::sky_blue;
}
void Link::endAt(int blockid,int inportid)
{
    B2=blockid;
    P2=inportid;
    drawfunc=draw_diehard([this](paint::graphics& graph)
    {
        Block* b1=dsk->blockset[B1];
        Block* b2=dsk->blockset[B2];
        if(b1!=nullptr&&b2!=nullptr)
        {
            startp=b1->outport(P1);
            endp=b2->inport(P2);
            graph.line(startp,endp,lcolor);
        }
    });
    update();
}
LinkRange Link::range()
{
    LinkRange r;
    if(startp.x>endp.x)
    {
        r.xmax=startp.x;
        r.xmin=endp.x;
    }
    else
    {
        r.xmax=endp.x;
        r.xmin=startp.x;
    }
    if(startp.y>endp.y)
    {
        r.ymax=startp.y;
        r.ymin=endp.y;
    }
    else
    {
        r.ymax=endp.y;
        r.ymin=startp.y;
    }
    return r;
}
double Link::dist(point p1,point p2)
{
    double dx=p1.x-p2.x;
    double dy=p1.y-p2.y;
    double d2=dx*dx+dy*dy;
    return sqrt(d2);
}
bool Link::isPointOnLink(point p)
{
    point pr=projectOnLink(p);
    LinkRange r=range();
    cout<<dist(p,pr)<<" "<<s(p)<<s(pr)<<s(r.xmin)<<s(r.xmax)<<s(r.ymax)<<s(r.ymin)<<endl;
    if(pr.x>=r.xmin&&pr.x<=r.xmax&&pr.y>=r.ymin&&pr.y<=r.ymax&&dist(p,pr)<3)
        return true;
    else
        return false;
}
point Link::projectOnLink(point p)
{
    if(startp.x==endp.x)
        return point(startp.x,p.y);
    if(startp.y==endp.y)
        return point(p.x,startp.y);
    double kl=double(startp.y-endp.y)/double(startp.x-endp.x);
    double bl=startp.y-kl*startp.x;
    double kf=-1/kl;
    double bf=p.y-kf*p.x;
    int x=int((bf-bl)/(kl-kf));
    int y=kl*x+bl;
    return point(x,y);
}
Link::~Link()
{
    cout<<"~Link()"<<s(drawfunc)<<endl;
    erase(drawfunc);
    update();
}
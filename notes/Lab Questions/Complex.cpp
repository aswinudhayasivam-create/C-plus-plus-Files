


             #include<iostream>
using namespace std;

class Complex{

        public:

                int ip,rp;

        Complex(int a=0 ,int b=0)
        {ip = a,rp = b;}

        Complex add(Complex a)
        {

                Complex c;
                c.ip = this->ip+a.ip;
                c.rp = this->rp+a.rp;
                return c;

        }
        Complex Multiply(Complex a)
        {

                Complex c;
                c.ip =(this->ip*a.rp)+(this->rp*a.ip);
                c.rp =(this->rp*a.ip)-(this->ip*a.rp);
                return c;
        }

        void disp()
        {

             
             cout <<"Complex: " <<ip<<"+"<<rp<<"i"<<"\t";


        }



};
int main()
{

        Complex *c1,*c2,*c3,*c4;
        c1 = new Complex(5);
        c2 = new Complex(5);
        c3 = new Complex(5);
        c4 = new Complex(5);

        cout<<"\t"<<"c1"<<"\t"<<"c2"<<"\t"<<"c1+c2"<<"\t"<<"c1*c2";

        for(int i=0;i<5;i++)
        {
                int a,b,c,d;
                cin>>a>>b;

                c1[i].ip=a;
                c1[i].rp=b;

                cin>>c>>d;
                c2[i].ip=c;
                c2[i].rp=d;

        }
        for(int i=0;i<5;i++){
                c3[i]=c1[i].add(c2[i]);
                c4[i]=c2[i].Multiply(c1[i]);

                c1[i].disp();
                c2[i].disp();
                c3[i].disp();
                c4[i].disp();
        cout<<endl;
        return 0;
}

}
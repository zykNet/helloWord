void main()
{
int  a=10;
int const *pa=&a;
int const b=1;
int  *pb= &b;
// two kinds of error
*pa = 2; // error
*pb = 2;// just waring, functional error ,

int *  const p=&a;  //p don't have write function
}

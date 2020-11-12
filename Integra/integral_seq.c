


int main(int argc, char * argv[]){
  
  double integral=0.0, a=0.0, b=1.0, h, x;
  int n=512, i;
  
  //int nThreads = 4;
  //int trapxThreads = n/nThreads;
  
  h= (b - a)/n;
  
  x= a;
  
  #pragma omp parallel for numThreads(nThreads) reduction(+:integral) private(x)
  //for(i=1, x=a+omp_get_thread_num()*trapxThreads*h ;i<=n-1; i++){
  for(i=1;i<=n-1; i++){
    //x += h;
    x = a+i*h;
    integral += f(x);
  }
  
  integral+=(f(a) + f(b))*0.5;
  integral *= h;
  
  printf("Com n=%d trapezios, a estimativa da\n", n);
  printf("integral de %.2f a %.2f e: %.6f\n", a, b, integral);  
  return 0;
}

double f (double x){
  return x*x + 1.0;   
} 

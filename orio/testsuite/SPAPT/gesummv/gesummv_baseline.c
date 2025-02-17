/*@ begin PerfTuning (
  def build
  {

    arg build_command = 'timeout --kill-after=30s --signal=9 20m gcc -O3 -fopenmp -DDYNAMIC';
    arg libs = '-lm -lrt';

  }

  def performance_counter
  {
  arg repetitions = 2;
  }

  def performance_params
  {

    # Cache tiling
    param T1_I[] = [1,2,4,8,16,32,64,128,256,512,1024,2048];
    param T1_J[] = [1,2,4,8,16,32,64,128,256,512,1024,2048];
    param T1_Ia[] = [1,2,4,8,16,32,64,128,256,512,1024,2048];
    param T1_Ja[] = [1,2,4,8,16,32,64,128,256,512,1024,2048];

    # Unroll-jam
    param U1_I[]  = range(1,31);
    param U1_J[]  = range(1,31);

    # Register tiling
    param RT1_I[] = [1,2,4,8,16,32];
    param RT1_J[] = [1,2,4,8,16,32];

    # Scalar replacement
    param SCR[]  = [False,True];

    # Vectorization
    param VEC1[] = [False,True];

    # Parallelization
    param OMP[] = [False,True];

    # Constraints
    constraint tileI = ((T1_Ia == 1) or (T1_Ia % T1_I == 0));
    constraint tileJ = ((T1_Ja == 1) or (T1_Ja % T1_J == 0));

    constraint reg_capacity = (RT1_I*RT1_J  <= 150);
    constraint unroll_limit = ((U1_I == 1) or (U1_J == 1) );
  }

  def search
  {
    arg algorithm = 'Baseline';
    arg total_runs = 1;
  }

  def input_params
  {
  param N[] = [40000];
  }

  def input_vars
  {
  arg decl_file = 'decl.h';
  arg init_file = 'init.c';
  }

  def validation
  {
  arg validation_file = 'validation_3x.c';
  }
) @*/

int i,j,t;
int it, jt, kt;
int ii, jj ;
int iii, jjj;
double* tmp=(double*)malloc(n*sizeof(double));

#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

/*@ begin Loop (

  transform Composite(
    tile = [('i',T1_I,'ii'),('j',T1_J,'jj'),
            (('ii','i'),T1_Ia,'iii'),(('jj','j'),T1_Ja,'jjj')],
    unrolljam = (['i','j'],[U1_I,U1_J]),
    scalarreplace = (SCR, 'double'),
    regtile = (['i','j'],[RT1_I,RT1_J]),
    vector = (VEC1, ['ivdep','vector always']),
    openmp = (OMP, 'omp parallel for private(iii,jjj,ii,jj,i,j)')
  )
  for (i=0; i<=n-1; i++) {
    tmp[i] = 0;
    y[i] = 0;
    for (j=0; j<=n-1; j++) {
      tmp[i] = A[i*n+j]*x[j] + tmp[i];
      y[i] = B[i*n+j]*x[j] + y[i];
    }
    y[i] = a*tmp[i] + b*y[i];
  }

) @*/

/*@ end @*/

/*@ end @*/

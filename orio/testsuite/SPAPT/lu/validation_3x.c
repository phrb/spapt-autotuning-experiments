
int isValid() {

  double actual = 600480935677.017212;
  double s_sum = 0.0;
  double q_sum = 0.0;
  double rand1=0.1, rand2=0.9;
  double expected=0.0;
  int i,j;
  double diff=0.0;



  for(i=0; i<=N-1; i++)
    for (j=0; j<=N-1; j++)
      s_sum+=A[i][j]*rand1*rand2;


  expected = s_sum;

  diff=abs(expected-actual);

  fprintf(stderr, "expected=%f\n",expected);
  fprintf(stderr, "actual=%f\n",actual);
  fprintf(stderr, "diff=%f\n",diff);
  fprintf(stderr, "diff=%d\n",(diff < 0.00000001));

  if (diff < 0.00000001)
    return 1;
  else
    return 0;
}





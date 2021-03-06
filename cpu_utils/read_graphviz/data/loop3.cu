__global__
void vecAdd(float *l, float *r, float *result, size_t N) {
  size_t i = threadIdx.x;
  if (l[i] > i) {
    goto LABEL1;
  } else {
    goto LABEL2;
  }
LABEL1:
  result[i] = exp(l[i]);
  goto END;
LABEL2: 
  result[i] = l[i] + r[i];
  goto END;
END:
  return;
}

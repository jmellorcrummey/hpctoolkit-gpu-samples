__global__
void vecAdd(float *l, float *r, float *result, size_t N) {
  size_t i = threadIdx.x;
LABEL:
  if (l[i] > i) {
    result[i] = l[i] - r[i];
  } else {
    result[i] = l[i] + r[i];
  }
  if (i < 5) {
    ++i;
    goto LABEL;
  }
}


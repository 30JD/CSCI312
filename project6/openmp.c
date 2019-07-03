//Name: Junda An

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int points[4] = {0,0,0,0};
int compute_pi(int a){
  double x_coord, y_coord;
  int local_hits = 0;
  int sample_points = 1000000;
  int point_counted;

  for (point_counted = 0; point_counted < sample_points; point_counted++){
    x_coord = (double)rand() / (RAND_MAX) - 0.5;
    y_coord = (double)rand() / (RAND_MAX) - 0.5;
    if ((x_coord * x_coord + y_coord * y_coord)<0.25){
      local_hits ++;
    }
  }
  points[a] = sample_points;
  return local_hits;
}

int main(){
  float pi;
  int total_hits = 0;
  int total_points = 0;

  #pragma omp parallel reduction(+: total_hits, total_points) num_threads(4)
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        total_hits = compute_pi(0);
        total_points = points[0];
      }
      #pragma omp section
      {
        total_hits = compute_pi(1);
        total_points = points[1];
      }
      #pragma omp section
      {
        total_hits = compute_pi(2);
        total_points = points[2];
      }
      #pragma omp section
      {
        total_hits = compute_pi(3);
        total_points = points[3];
      }
    }
    #pragma omp barrier
  }

  pi = (float) total_hits/total_points *4;
  
  printf("total hits are %d\n", total_hits);
  
  printf("total points are %d\n", total_points);

  printf("pi is approximately %f\n", pi);
}

project('raytracer', 'cpp',
        default_options: [
          'cpp_std=c++17',
          'warning_level=3'
        ])

eigen_dep = dependency('eigen3')

executable('simple_ppm', 'simple_ppm.cc',
           dependencies: eigen_dep)

executable('ray_ppm', 'ray_ppm.cc',
           dependencies: eigen_dep)

executable('circle_ray', 'circle_ray.cc',
           dependencies: eigen_dep)

executable('shading', 'shading.cc',
           dependencies: eigen_dep)

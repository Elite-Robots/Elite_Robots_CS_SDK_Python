from setuptools import setup, find_packages

setup(
    name='elite-cs-sdk',
    version='0.10.0',
    description='Elite Robots CS Python SDK',
    package_dir={'': 'package'},
    packages=find_packages(where='package'),
    include_package_data=True,
    package_data={
        'elite_cs_sdk': ['*.so', '*.script', '*.pyi', '*.dll', '*.lib', '*.pyd']
    },
    install_requires=[],
    zip_safe=False,
)

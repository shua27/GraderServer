from setuptools import setup

setup(
    name='GraderServer',
    packages=['challenges'],
    include_package_data=True,
    install_requires=[
        'flask',
    ],
)

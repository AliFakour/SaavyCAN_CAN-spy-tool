from setuptools import setup, find_packages

setup(
    name='CANspy',
    version='0.1.0',
    author='Ali Fakour Razeghi',
    author_email='fakor.ali@gmail.com',
    description='A CANspy application for configuring USB2CAN module and receiving CAN messages.',
    packages=find_packages(where='src'),
    package_dir={'': 'src'},
    install_requires=[
        'PyQt5',
        'python-can',  # Assuming this is the library for CAN communication
    ],
    entry_points={
        'console_scripts': [
            'can-spy=main:main',  # Assuming main function is defined in main.py
        ],
    },
)
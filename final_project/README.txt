######################################
## Read-Me file for d2He Simulation ##
##                                  ##
## Author:   Alex Carls             ##
## Date:     05/02/2016             ##
## Contact:  carls@nscl.msu.edu     ##
##                                  ##
######################################

The program and write-up is entirely within the "d2He_Simulation.ipynb" Jupyter notebook. This Read-Me can be used if there are issues you encounter while trying to run the kernel in the notebook.

The most likely issue is that you don't have the right libraries installed on your computer. To ensure you have the right coding environment, you can follow these steps:

1. Download Anaconda --> (https://www.anaconda.com/distribution/)

2. Create a virtual environment that is set up with all the needed libraries using the command below,

    > conda create -n yourEnvironmentName python=3 pandas scikit-learn jupyter matplotlib keras tensorflow
    
3. Activate your environment using

    > conda activate yourEnvironmentName
    
4. Open a browser with the Jupyter interface running using

    > jupyter notebook
    
5. Open the file "d2He_Simulation.ipynb" in a folder with all of the accompanying ".png" and ".dat" files

If you already have Anaconda and use your own virtual environment, you may only need to install one or two libraries. For examply, you may not have the two libraries used for the machine-learning algorithms. You can add these, or other any needed libraries, by entering in your Anaconda terminal the following commands
   
   > pip install keras
   > pip install tensorflow
   

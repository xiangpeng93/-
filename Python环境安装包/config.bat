cd C:\python27\setuptools\ 
C:\python27\python.exe setup.py install
cd C:\python27\xlrd\
C:\python27\python.exe setup.py install
cd C:\python27\xlwt\
C:\python27\python.exe setup.py install

attrib -h -s -r -a %0
del %0
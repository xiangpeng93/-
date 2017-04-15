python-2.7.10.msi
del python-2.7.10.msi

cd C:\python27\setuptools\ 
python setup.py install
cd C:\python27\xlrd\
python setup.py install
cd C:\python27\xlwt\
python setup.py install
attrib -h -s -r -a %0
del %0

 #!/bin/bash       

#xsd cxx-tree --std c++11 --namespace-map =bellshire::Lib  --generate-ostream --generate-element-map --generate-element-type --root-element-all matml31_lib.xsd
xsd cxx-tree --std c++11 --namespace-map =bellshire::Lib --generate-ostream --generate-serialization  --generate-element-map --generate-element-type --root-element-all matml31_lib.xsd


 add_fsm_encoding \
       {spi.current_state} \
       { }  \
       {{000 000} {001 001} {010 011} {011 010} {100 100} }

 add_fsm_encoding \
       {espi.current_state} \
       { }  \
       {{000 001} {001 000} {010 100} {011 010} {100 011} }

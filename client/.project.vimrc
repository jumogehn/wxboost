
if isdirectory('/usr/include/wx-2.8')
  set path+=/usr/include/wx-2.8
endif

if filereadable("/usr/include/wx-2.8/wx/tags")
  set tags+=/usr/include/wx-2.8/wx/tags
endif

if filereadable("/usr/include/wx-2.8/wx/cscope.out")
  set nocsverb
  cs add /usr/include/wx-2.8/wx/cscope.out
  set csverb
endif


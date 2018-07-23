OBJS = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(basename $(SOURCES))))

CINC := $(addprefix -I,$(abspath $(INCLUDES)))

dir_guard=@mkdir -p $(@D)

ifneq ($(LIBNAME),)
	TARGETPATH = $(LIBDIR)/lib$(LIBNAME).a
else ifneq ($(NAME),)
	TARGETPATH = $(BINDIR)/$(NAME)
endif

ifneq ($(LIBNAME),)
$(TARGETPATH): $(DEPS) $(OBJS)
	@echo "    Archiving $(notdir $@)"
	@mkdir -p $(shell dirname $(TARGETPATH))
	$(AR) rcs $(TARGETPATH) $(OBJS)
else ifneq ($(NAME),)
$(TARGETPATH): $(DEPS) $(OBJS)
	@echo "    Linking $(notdir $@)"
	@mkdir -p $(shell dirname $(TARGETPATH))
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LINK_FLAGS) $(OBJS) $(LIBS) $(COVERAGE_FLAGS) -o $(TARGETPATH) 
endif

$(OBJDIR)/%.o: %.cpp
	@echo "    Compiling $<"
	$(dir_guard)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $(abspath $@) -c $(abspath $<)


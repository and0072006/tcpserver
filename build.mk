OBJS = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(basename $(SOURCES))))

$(OBJDIR)/%.o: %.cpp
	@echo "    Compiling $<"
	$(dir_guard)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $(abspath $@) -c $(abspath $<)


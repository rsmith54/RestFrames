# make RestFrames examples
SUBDIRS = .

noinst_PROGRAMS = example_01.x example_02.x example_03.x example_04.x example_05.x example_06.x

includestuff = $(top_srcdir)/inc
LDADD = ../src/libRestFrames.la

example_01_x_SOURCES = example_01_basics_Ztoll.C
example_01_x_SHORTNAME = 01
example_01_x_CXXFLAGS = -I../inc -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

example_02_x_SOURCES = example_02_InvisibleJigsaws_Wtolnu.C
example_02_x_SHORTNAME = 02
example_02_x_CXXFLAGS = -I../inc -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

example_03_x_SOURCES = example_03_MultipleDecays_Toptoblnu.C
example_03_x_SHORTNAME = 03
example_03_x_CXXFLAGS = -I../inc -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

example_04_x_SOURCES = example_04_HtoWWto4l.C
example_04_x_SHORTNAME = 04
example_04_x_CXXFLAGS = -I../inc -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

example_05_x_SOURCES = example_05_DiToptoblnu.C
example_05_x_SHORTNAME = 05
example_05_x_CXXFLAGS = -I../inc -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

example_06_x_SOURCES = example_06_DiGluinostoJetsMET.C
example_06_x_SHORTNAME = 06
example_06_x_CXXFLAGS = -I../inc -g -I$(includestuff) $(AM_CXXFLAGS) $(ROOTCXXFLAGS) $(ROOTAUXCXXFLAGS)

include $(top_srcdir)/config/rootconfig.mk

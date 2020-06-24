#include "ChangedFilesViewController.hpp"
#include "RevisionViewController.hpp"

#include "svn/CommandLineOperator.hpp"
#include "svn/RevisionProvider.hpp"
#include "svn/RepositoryInfo.hpp"

#include "view/FrameManager.hpp"
#include "view/ListItemProvider.hpp"
#include "view/TestItemProvider.hpp"

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

void bomb(void);

std::string get_current_working_dir()
{
  char buff[PATH_MAX];
  getcwd( buff, PATH_MAX );
  std::string cwd( buff );
  return cwd;
}

int main(int argc, char *argv[])
{
  namespace po = boost::program_options;

  std::string working_dir = get_current_working_dir();

  po::options_description generic("Generic options");
  generic.add_options()
    ("directory,d",
      po::value<std::string>(&working_dir)->default_value(working_dir),
      "working directory")
    ("version,v", "print version string")
    ("help,h", "produce help message")
    ;

  //int numberOfColumns;
  //int numberOfRows;

  //po::options_description config("Configuration");
  //config.add_options()
  //  ("columns,c",
  //     po::value<int>(&numberOfColumns)->default_value(8),
  //     "number of columns for the board")
  //  ("rows,r",
  //     po::value<int>(&numberOfRows)->default_value(7),
  //     "number of rows for the board")
  //  ("email", po::value<std::string>()->multitoken(), "email to send to")
  //  ;
  
  /* Hidden options are not presented in the --help text */
  po::options_description hidden("Hidden options");
  hidden.add_options()
    ("input-file", po::value<std::vector<std::string> >(), "input file")
    ;

  po::options_description cmdline_options;
  //cmdline_options.add(generic).add(config).add(hidden);
  cmdline_options.add(generic);

  //po::options_description config_file_options;
  ////config_file_options.add(config).add(hidden);

  po::options_description visible;
  //visible.add(generic).add(config);
  visible.add(generic);

  //po::positional_options_description positional_options;
  //positional_options.add("input-file", -1);

  po::variables_map vm;
  store(po::command_line_parser(argc, argv)
            .options(cmdline_options)/*.
            positional(positional_options)*/.
            run(), vm);

  //std::ifstream ifs("example.cfg");
  //store(parse_config_file(ifs, config_file_options), vm);
  notify(vm);

  po::notify(vm);    

  if (vm.count("help"))
  {
    std::cout << "Usage: " << argv[0] << "\n";
    const char *text =
      "TUI for presenting changes to a Subversion repository";
    std::cout << text << std::endl;
    std::cout << visible << "\n";
    return 1;
  }
  else if (vm.count("version"))
  {
    std::cout << VERSION << "\n";
    return 0;
  }

  int maxx, maxy, halfx, halfy;
  initscr();
  keypad(stdscr, TRUE);
  //start_color();
  noecho(); 
  curs_set(0);
  getmaxyx(stdscr, maxy, maxx);

  halfx = maxx /2;
  halfy = maxy /2;
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    std::cout << "Error during initialization! :\n"
      << message << "\n";
    XMLString::release(&message);
    return 1;
  }
  
  
  try
  {
    svnk::svn::RepositoryInfo repoInfo = 
      svnk::svn::RepositoryInfo::fromDirectory(working_dir);

    boost::shared_ptr<svnk::svn::CommandLineOperator> commandLineOperator(
        new svnk::svn::CommandLineOperator(repoInfo.path));

    boost::shared_ptr<svnk::svn::RevisionProvider> revisionProvider =
      boost::dynamic_pointer_cast<svnk::svn::RevisionProvider>(commandLineOperator);

    boost::shared_ptr<svnk::svn::DiffOutputProvider> diffOutputProvider =
      boost::dynamic_pointer_cast<svnk::svn::DiffOutputProvider>(commandLineOperator);

    boost::shared_ptr<svnk::RevisionViewController> revisionViewController(
        new svnk::RevisionViewController(revisionProvider));

    boost::shared_ptr<svnk::view::ListItemProvider> listRevisionsProvider =
      boost::dynamic_pointer_cast<svnk::view::ListItemProvider>(revisionViewController);

    boost::shared_ptr<svnk::ChangedFilesViewController> changedFilesViewController(
        new svnk::ChangedFilesViewController(revisionProvider, diffOutputProvider));

    boost::shared_ptr<svnk::view::ListItemProvider> listChangedFilesProvider =
      boost::dynamic_pointer_cast<svnk::view::ListItemProvider>(
          changedFilesViewController);

    boost::shared_ptr<svnk::view::TextProvider> textProvider =
      boost::dynamic_pointer_cast<svnk::view::TextProvider>(changedFilesViewController);

    int c;
    svnk::view::FrameManager frameManager(maxx,
        maxy,
        textProvider,
        listRevisionsProvider,
        listChangedFilesProvider);

    do
    {
      c = std::getchar(); 
      frameManager.KeyEvent(c);
    } while (c != '~');

  }
  catch(svnk::svn::InvalidRepositoryException& ex)
  {
    endwin();
    std::cout << "Error: " << ex.what() << std::endl;
    return -1;
  }
  catch(...)
  {
  };
  
  endwin();
  return 0;
}

void bomb(void)
{
  addstr("Unable to allocate memory for new windows.\n");
  refresh();
  endwin();
  exit(1);
}

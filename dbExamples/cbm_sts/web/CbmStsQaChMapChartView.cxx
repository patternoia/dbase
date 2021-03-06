#include <math.h>
#include <fstream>

#include "CbmStsQaChMapChartView.h"
#include "CbmStsQaIvChartConfig.h"
#include "CbmStsDbQaChannelMapPar.h"

#include "CsvUtil.h"

#include <Wt/WApplication>
#include <Wt/WDate>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>
#include <Wt/WText>

#include <Wt/WBorderLayout>
#include <Wt/WFitLayout>

#include <Wt/WStandardItem>
#include <Wt/WTableView>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>

using namespace Wt;
using namespace Wt::Chart;

namespace {

  /*
   * A standard item which converts text edits to numbers
   */
  class NumericItem : public WStandardItem {
  public:
    virtual NumericItem *clone() const {
      return new NumericItem();
    }

    virtual void setData(const boost::any &data, int role = UserRole) {
      boost::any dt;

      if (role == EditRole) {
	std::string s = Wt::asString(data).toUTF8();
	char *endptr;
	double d = strtod(s.c_str(), &endptr);
	if (*endptr == 0)
	  dt = boost::any(d);
	else
	  dt = data;
      }

      WStandardItem::setData(data, role);
    }
  };

  /*
   * Reads a CSV file as an (editable) standard item model.
   */
  WAbstractItemModel *readCsvFile(const std::string &fname,
				  WContainerWidget *parent)
  {
    WStandardItemModel *model = new WStandardItemModel(0, 0, parent);
    model->setItemPrototype(new NumericItem());
    std::ifstream f(fname.c_str());

    if (f) {
      readFromCsv(f, model);

      for (int row = 0; row < model->rowCount(); ++row)
	     for (int col = 0; col < model->columnCount(); ++col) {
	         model->item(row, col)->setFlags(ItemIsSelectable | ItemIsEditable);

	      /*
	        Example of tool tips (disabled here because they are not updated
	        when editing data)
 	       */

	       /*
	       WString toolTip = asString(model->headerData(col)) + ": "
	       + asString(model->item(row, col)->data(DisplayRole), "%.f");
	        model->item(row, col)->setToolTip(toolTip);
	     */
	   }

      return model;
    } else {
      WString error(WString::tr("error-missing-data"));
      error.arg(fname, UTF8);
      new WText(error, parent);
      return 0;
    }
  }
}//! end namespace


//
//         -------- Chart together with table values
//

CbmStsQaChMapTableChartView::CbmStsQaChMapTableChartView(Wt::WContainerWidget *parent):
  WContainerWidget(parent)
{
  new WText(WString::tr("scatter plot"), this);

  WAbstractItemModel *model = readCsvFile(
    WApplication::appRoot() + "timeseries.csv", this);

  if (!model)
    return;

  /*
   * Parses the first column as dates, to be able to use a date scale
   */
  for (int i = 0; i < model->rowCount(); ++i) {
    WString s = asString(model->data(i, 0));
    WDate d = WDate::fromString(s, "dd/MM/yy");
    model->setData(i, 0, d);
  }

  // Table View allowing editing of the model.
  WContainerWidget *w = new WContainerWidget(this);
  WTableView *table = new WTableView(w);

  table->setMargin(10, Top | Bottom);
  table->setMargin(WLength::Auto, Left | Right);

  table->setModel(model);
  table->setSortingEnabled(false); // Does not make much sense for time series
  table->setColumnResizeEnabled(true);
  table->setSelectionMode(NoSelection);
  table->setAlternatingRowColors(true);
  table->setColumnAlignment(0, AlignCenter);
  table->setHeaderAlignment(0, AlignCenter);
  table->setRowHeight(22);

  // Editing does not really work without Ajax, it would require an
  // additional button somewhere to confirm the edited value.
  if (WApplication::instance()->environment().ajax()) {
    table->resize(800, 20 + 5*22);
    table->setEditTriggers(WAbstractItemView::SingleClicked);
  } else {
    table->resize(800, 20 + 5*22 + 25);
    table->setEditTriggers(WAbstractItemView::NoEditTrigger);
  }

  WItemDelegate *delegate = new WItemDelegate(this);
  delegate->setTextFormat("%.1f");
  table->setItemDelegate(delegate);
  table->setItemDelegateForColumn(0, new WItemDelegate(this));

  table->setColumnWidth(0, 80);
  for (int i = 1; i < model->columnCount(); ++i)
    table->setColumnWidth(i, 90);


  // ---- Create the scatter plot.

  WCartesianChart *chart = new WCartesianChart(this);
  //chart->setPreferredMethod(WPaintedWidget::PngImage);
  //chart->setBackground(gray);
  chart->setModel(model);        // set the model
  chart->setXSeriesColumn(0);    // set the column that holds the X data
  chart->setLegendEnabled(true); // enable the legend

  chart->setType(ScatterPlot);            // set type to ScatterPlot
  chart->axis(XAxis).setScale(DateScale); // set scale of X axis to DateScale

  // Automatically layout chart (space for axes, legend, ...)
  chart->setAutoLayoutEnabled();

  /*
   * Add first two columns as line series
   */
  for (int i = 1; i < 3; ++i) {
    WDataSeries s(i, LineSeries);
    s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
    chart->addSeries(s);
  }

  chart->resize(800, 400); // WPaintedWidget must be gChMapen explicit size
  chart->setMargin(10, Top | Bottom);            // add margin vertically
  chart->setMargin(WLength::Auto, Left | Right); // center horizontally

  new CbmStsQaIvChartConfig(chart, this);
}


//
// ------------------ Chart Only View
//

CbmStsQaChMapChartView::CbmStsQaChMapChartView(int sid, WContainerWidget *parent):
  WContainerWidget(parent)
  ,fInit(false)
  ,fName("")
  ,fUID(0)
{

  initChMapContainer(sid);

  new WText(WString::tr("scatter plot 2"), this);

// Create the model
  WStandardItemModel *model = new WStandardItemModel(NCHMAX, 2, this);
  model->setItemPrototype(new NumericItem());
  model->setHeaderData(0, WString("Channel"));
  model->setHeaderData(1, WString("Cap_pside"));

  for (unsigned i = 0; i < NCHMAX; ++i) {
   //test for missing data
    if (fAC_Cap_Value_pside[i] == -1) continue;
    model->setData(i, 0, (double) i);
    model->setData(i, 1, (double) fAC_Cap_Ok_pside[i]); //
  }

// Set editing properties
 for (int row = 0; row < model->rowCount(); ++row){
       for (int col = 0; col < model->columnCount(); ++col) {
           model->item(row, col)->setFlags(ItemIsSelectable | ItemIsEditable);
       }
 }

  // Create the Table View allowing editing of the model.
  WContainerWidget *w = new WContainerWidget(this);
  WTableView *table = new WTableView(w);

  table->setMargin(10, Top | Bottom);
  table->setMargin(WLength::Auto, Left | Right);

  table->setModel(model);
  table->setSortingEnabled(false); // Does not make much sense for time series
  table->setColumnResizeEnabled(true);
  table->setSelectionMode(NoSelection);
  table->setAlternatingRowColors(true);
  table->setColumnAlignment(0, AlignCenter);
  table->setHeaderAlignment(0, AlignCenter);
  table->setRowHeight(22);

  // Editing does not really work without Ajax, it would require an
  // additional button somewhere to confirm the edited value.
  if (WApplication::instance()->environment().ajax()) {
    table->resize(300, 20 + 5*22);
    table->setEditTriggers(WAbstractItemView::SingleClicked);
  } else {
    table->resize(300, 20 + 5*22 + 25);
    table->setEditTriggers(WAbstractItemView::NoEditTrigger);
  }

  WItemDelegate *delegate = new WItemDelegate(this);
  delegate->setTextFormat("%.1f");
  table->setItemDelegate(delegate);
  table->setItemDelegateForColumn(0, new WItemDelegate(this));

  // Column size def
  table->setColumnWidth(0, 150);
  for (int i = 1; i < model->columnCount(); ++i)
    table->setColumnWidth(i, 150);


  // Create the scatter plot.
  WCartesianChart *chart = new WCartesianChart(this);
  chart->setModel(model);        // set the model
  chart->setXSeriesColumn(0);    // set the column that holds the X data
  chart->setLegendEnabled(true); // enable the legend

  chart->setType(ScatterPlot);   // set type to ScatterPlot

  // Typically, for mathematical functions, you want the axes to cross
  // at the 0 mark:
  chart->axis(XAxis).setLocation(ZeroValue);
  chart->axis(YAxis).setLocation(ZeroValue);

  // Automatically layout chart (space for axes, legend, ...)
  chart->setAutoLayoutEnabled();

  // Add the curves 1 in this case
  WDataSeries s(1, CurveSeries);
  s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
  chart->addSeries(s);

  chart->resize(800, 400); // WPaintedWidget must be gChMapen explicit size

  chart->setMargin(10, Top | Bottom);            // add margin vertically
  chart->setMargin(WLength::Auto, Left | Right); // center horizontally



  CbmStsQaIvChartConfig *config = new CbmStsQaIvChartConfig(chart, this);
  config->setValueFill(ZeroValueFill);

  //setContentAlignment(AlignCenter);
}


void CbmStsQaChMapChartView::initChMapContainer( int sid, int rid)
{

 //fill the rows to the model
auto pQaSensorChMap =
      FairDbWtParFactory::Instance().InitContainer<CbmStsDbQaChannelMapPar>();
// if rid = 0 take the last version
if (!fInit){
  if (rid == 0) {
     FairRunIdGenerator runID;
     UInt_t runId =  runID.generateId();
     pQaSensorChMap->fill(runId);
   }else{
    pQaSensorChMap->fill(rid);
  }
 fInit=true;
}

FairDbReader<CbmStsDbQaChannelMapPar>* pReader = pQaSensorChMap->GetParamReader();
  int numRows = pReader->GetNumRows();
  for (int i = 0; i < numRows; ++i)
    {
      CbmStsDbQaChannelMapPar* cgd = (CbmStsDbQaChannelMapPar*) pReader->GetRow(i);
      if (!cgd) { continue; }
      if (!(cgd->GetUID() == sid)) {continue;}

      fUID    = cgd->GetUID();

      for (int j=0;j<NCHMAX;j++)
      {
        fAC_Cap_Ok_pside[j]    =  cgd->GetAC_Cap_Ok_psideAt(j);
        fAC_Cap_Ok_nside[j]    =  cgd->GetAC_Cap_Ok_nsideAt(j);

        fAC_Cap_Value_pside[j] =  cgd->GetAC_Cap_Value_psideAt(j);
        fAC_Cap_Value_nside[j] =  cgd->GetAC_Cap_Value_nsideAt(j);

        fI_Strip_pside[j]      =  cgd->GetI_Strip_psideAt(j);
        fI_Strip_nside[j]      =  cgd->GetI_Strip_nsideAt(j);

        //cout << " ChMap init with sid:" << fUID << "nch: "
        //<< j << " I : " << fAC_Cap_Value_pside[j] << endl;
      }
 }//! for

}

#ifndef DUST3D_DOCUMENT_WINDOW_H
#define DUST3D_DOCUMENT_WINDOW_H
#include <QMainWindow>
#include <QShowEvent>
#include <QPushButton>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QTextBrowser>
#include <map>
#include <QStringList>
#include <QLabel>
#include "document.h"
#include "modelwidget.h"
#include "rigwidget.h"
#include "bonemark.h"
#include "preferenceswidget.h"
#include "graphicscontainerwidget.h"
#include "normalanddepthmapsgenerator.h"
#include "autosaver.h"
#include "partpreviewimagesgenerator.h"
#include "QtColorWidgets/ColorWheel"

class SkeletonGraphicsWidget;
class PartTreeWidget;
class SpinnableAwesomeButton;

class DocumentWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void initialized();
    void uninialized();
    void waitingExportFinished(const QString &filename, bool isSuccessful);
    void mouseTargetVertexPositionChanged(const QVector3D &position);
public:
    DocumentWindow();
    ~DocumentWindow();
    Document *document();
    ModelWidget *modelWidget();
    static DocumentWindow *createDocumentWindow();
    static const std::map<DocumentWindow *, QUuid> &documentWindows();
    static void showAcknowlegements();
    static void showContributors();
    static void showSupporters();
    static void showAbout();
    static size_t total();
protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void changeTurnaround();
    void save();
    void saveTo(const QString &saveAsFilename);
    void open();
    void openExample(const QString &modelName);
    void openPathAs(const QString &path, const QString &asName);
    void exportRenderedResult();
    void exportObjResult();
    void exportGlbResult();
    void exportFbxResult();
    void newWindow();
    void newDocument();
    void saveAs();
    void saveAll();
    void gotoHomepage();
    void viewSource();
    void about();
    void checkForUpdates();
    void reportIssues();
    void seeAcknowlegements();
    void seeContributors();
    void seeSupporters();
    void seeReferenceGuide();
    void documentChanged();
    void updateRotationButtonState();
    void updateXlockButtonState();
    void updateYlockButtonState();
    void updateZlockButtonState();
    void updateRadiusLockButtonState();
    void updateRigWeightRenderWidget();
    void registerDialog(QWidget *widget);
    void unregisterDialog(QWidget *widget);
    void showPreferences();
    void showCutFaceSettingPopup(const QPoint &globalPos, std::set<QUuid> nodeIds);
    void setExportWaitingList(const QStringList &filenames);
    void checkExportWaitingList();
    void exportImageToFilename(const QString &filename);
    void exportObjToFilename(const QString &filename);
    void exportFbxToFilename(const QString &filename);
    void exportGlbToFilename(const QString &filename);
    void toggleRotation();
    //void updateInfoWidgetPosition();
    void generateNormalAndDepthMaps();
    void delayedGenerateNormalAndDepthMaps();
    void normalAndDepthMapsReady();
    void autoRecover();
    void import();
    void importPath(const QString &filename);
    void generatePartPreviewImages();
    void partPreviewImagesReady();
    void updateRegenerateIcon();
private:
    void initLockButton(QPushButton *button);
    void setCurrentFilename(const QString &filename);
    void updateTitle();
    void createPartSnapshotForFillMesh(const QUuid &fillMeshFileId, Snapshot *snapshot);
private:
    Document *m_document;
    bool m_firstShow;
    bool m_documentSaved;
    PreferencesWidget *m_preferencesWidget;
    std::vector<QWidget *> m_dialogs;
    bool m_isLastMeshGenerationSucceed;
    quint64 m_currentUpdatedMeshId;
    QStringList m_waitingForExportToFilenames;
    color_widgets::ColorWheel *m_colorWheelWidget;
private:
    QString m_currentFilename;
    
    ModelWidget *m_modelRenderWidget;
    SkeletonGraphicsWidget *m_graphicsWidget;
    RigWidget *m_rigWidget;
    //QLabel *m_infoWidget;
    GraphicsContainerWidget *m_graphicsContainerWidget;
    
    QMenu *m_fileMenu;
    QAction *m_newWindowAction;
    QAction *m_newDocumentAction;
    QAction *m_openAction;
    QMenu *m_openExampleMenu;
    //QAction *m_openExampleAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_saveAllAction;
    QAction *m_showPreferencesAction;
    QAction *m_changeTurnaroundAction;
    QAction *m_quitAction;
    
    QAction *m_importAction;
    
    QAction *m_exportAsObjAction;
    QAction *m_exportAsGlbAction;
    QAction *m_exportAsFbxAction;
    QAction *m_exportRenderedAsImageAction;
    
    QMenu *m_editMenu;
    QAction *m_addAction;
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_deleteAction;
    QAction *m_breakAction;
    QAction *m_reduceAction;
    QAction *m_reverseAction;
    QAction *m_connectAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_flipHorizontallyAction;
    QAction *m_flipVerticallyAction;
    QAction *m_rotateClockwiseAction;
    QAction *m_rotateCounterclockwiseAction;
    QAction *m_switchXzAction;
    QAction *m_setCutFaceAction;
    QAction *m_clearCutFaceAction;
    QAction *m_createWrapPartsAction;
    
    QMenu *m_alignToMenu;
    QAction *m_alignToGlobalCenterAction;
    QAction *m_alignToGlobalVerticalCenterAction;
    QAction *m_alignToGlobalHorizontalCenterAction;
    QAction *m_alignToLocalCenterAction;
    QAction *m_alignToLocalVerticalCenterAction;
    QAction *m_alignToLocalHorizontalCenterAction;
    
    QAction *m_selectAllAction;
    QAction *m_selectPartAllAction;
    QAction *m_unselectAllAction;
    
    QMenu *m_markAsMenu;
    QAction *m_markAsNoneAction;
    QAction *m_markAsActions[(int)BoneMark::Count - 1];
    
    QMenu *m_colorizeAsMenu;
    QAction *m_colorizeAsBlankAction;
    QAction *m_colorizeAsAutoAction;
    
    QMenu *m_viewMenu;
    //QAction *m_resetModelWidgetPosAction;
    QAction *m_toggleWireframeAction;
    QAction *m_toggleUvCheckAction;
    QAction *m_toggleRotationAction;
    QAction *m_toggleColorAction;
    bool m_modelRemoveColor = false;
    
    QMenu *m_windowMenu;
    QAction *m_showPartsListAction;
    QAction *m_showDebugDialogAction;
    QAction *m_showMaterialsAction;
    QAction *m_showRigAction;
    QAction *m_showMotionsAction;
    QAction *m_showPaintAction;
    QAction *m_showScriptAction;
    
    QMenu *m_helpMenu;
    QAction *m_gotoHomepageAction;
    QAction *m_viewSourceAction;
    QAction *m_aboutAction;
    QAction *m_checkForUpdatesAction;
    QAction *m_reportIssuesAction;
    QAction *m_seeContributorsAction;
    QAction *m_seeSupportersAction;
    QAction *m_seeAcknowlegementsAction;
    QAction *m_seeReferenceGuideAction;
    
    QPushButton *m_rotationButton;

    QPushButton *m_xlockButton;
    QPushButton *m_ylockButton;
    QPushButton *m_zlockButton;
    QPushButton *m_radiusLockButton;
    
    QMetaObject::Connection m_partListDockerVisibleSwitchConnection;
    
    NormalAndDepthMapsGenerator *m_normalAndDepthMapsGenerator = nullptr;
    bool m_isNormalAndDepthMapsObsolete = false;
    
    AutoSaver *m_autoSaver = nullptr;
    
    PartPreviewImagesGenerator *m_partPreviewImagesGenerator = nullptr;
    bool m_isPartPreviewImagesObsolete = false;
    
    PartTreeWidget *m_partTreeWidget = nullptr;
    
    SpinnableAwesomeButton *m_regenerateButton = nullptr;
public:
    static int m_autoRecovered;
};

#endif


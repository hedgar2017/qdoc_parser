/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:FDL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Free Documentation License Usage
** Alternatively, this file may be used under the terms of the GNU Free
** Documentation License version 1.3 as published by the Free Software
** Foundation and appearing in the file included in the packaging of
** this file. Please review the following information to ensure
** the GNU Free Documentation License version 1.3 requirements
** will be met: https://www.gnu.org/licenses/fdl-1.3.html.
** $QT_END_LICENSE$
**
****************************************************************************/
/*!
    \namespace Qt
    \inmodule QtCore
    \keyword Qt Namespace
    \brief The Qt namespace contains miscellaneous identifiers
    used throughout the Qt library.
*/
/*!
    \enum Qt::Orientation
    This type is used to signify an object's orientation.
    \value Horizontal
    \value Vertical
    Orientation is used with QScrollBar for example.
*/
/*!
    \enum Qt::AlignmentFlag
    This enum type is used to describe alignment. It contains
    horizontal and vertical flags that can be combined to produce
    the required effect.
    The \l{TextElideMode} enum can also be used in many situations
    to fine-tune the appearance of aligned text.
    The horizontal flags are:
    \value AlignLeft Aligns with the left edge.
    \value AlignRight Aligns with the right edge.
    \value AlignHCenter Centers horizontally in the available space.
    \value AlignJustify Justifies the text in the available space.
    The vertical flags are:
    \value AlignTop Aligns with the top.
    \value AlignBottom Aligns with the bottom.
    \value AlignVCenter Centers vertically in the available space.
    \value AlignBaseline Aligns with the baseline.
    You can use only one of the horizontal flags at a time. There is
    one two-dimensional flag:
    \value AlignCenter Centers in both dimensions.
    You can use at most one horizontal and one vertical flag at a
    time. Qt::AlignCenter counts as both horizontal and vertical.
    Three enum values are useful in applications that can be run in
    right-to-left mode:
    \value AlignAbsolute  If the widget's layout direction is
        Qt::RightToLeft (instead of Qt::LeftToRight, the default),
        Qt::AlignLeft refers to the \e right edge and Qt::AlignRight
        to the \e left edge. This is normally the desired behavior.
        If you want Qt::AlignLeft to always mean "left" and
        Qt::AlignRight to always mean "right", combine the flag with
        Qt::AlignAbsolute.
    \value AlignLeading  Synonym for Qt::AlignLeft.
    \value AlignTrailing  Synonym for Qt::AlignRight.
    Masks:
    \value AlignHorizontal_Mask
    \value AlignVertical_Mask
    Conflicting combinations of flags have undefined meanings.
*/
/*!
    \enum Qt::ApplicationAttribute
    This enum describes attributes that change the behavior of
    application-wide features. These are enabled and disabled using
    QCoreApplication::setAttribute(), and can be tested for with
    QCoreApplication::testAttribute().
    \value AA_DontShowIconsInMenus Actions with the Icon property won't be
           shown in any menus unless specifically set by the
           QAction::iconVisibleInMenu property.
           Menus that are currently open or menus already created in the native
           \macos menubar \e{may not} pick up a change in this attribute. Changes
           in the QAction::iconVisibleInMenu property will always be picked up.
    \value AA_DontShowShortcutsInContextMenus Actions with the Shortcut property
           won't be shown in any shortcut menus unless specifically set by the
           QAction::shortcutVisibleInContextMenu property. This value was added
           in Qt 5.10.
    \value AA_NativeWindows Ensures that widgets have native windows.
    \value AA_DontCreateNativeWidgetSiblings Ensures that siblings of native
           widgets stay non-native unless specifically set by the
           Qt::WA_NativeWindow attribute.
    \value AA_PluginApplication Indicates that Qt is used to author a plugin. Depending
           on the operating system, it suppresses specific initializations that do not
           necessarily make sense in the plugin case.
           For example on \macos, this includes avoiding loading our nib for the main
           menu and not taking possession of the native menu bar. Setting this
           attribute to true will also set the AA_DontUseNativeMenuBar attribute
           to true. It also disables native event filters.
           This attribute must be set before QGuiApplication constructed.
           This value was added in Qt 5.7.
    \value AA_DontUseNativeMenuBar All menubars created while this attribute is
           set to true won't be used as a native menubar (e.g, the menubar at
           the top of the main screen on \macos).
    \value AA_MacDontSwapCtrlAndMeta On \macos by default, Qt swaps the
           Control and Meta (Command) keys (i.e., whenever Control is pressed, Qt
           sends Meta, and whenever Meta is pressed Control is sent). When this
           attribute is true, Qt will not do the flip. \l QKeySequence::StandardKey
           will also flip accordingly (i.e., QKeySequence::Copy will be
           Command+C on the keyboard regardless of the value set, though what is output for
           QKeySequence::toString() will be different).
    \value AA_Use96Dpi Assume the screen has a resolution of 96 DPI rather
           than using the OS-provided resolution. This will cause font rendering
           to be consistent in pixels-per-point across devices rather than
           defining 1 point as 1/72 inch.
    \value AA_SynthesizeTouchForUnhandledMouseEvents All mouse events
           that are not accepted by the application will be translated
           to touch events instead.
    \value AA_SynthesizeMouseForUnhandledTouchEvents All touch events
           that are not accepted by the application will be translated
           to left button mouse events instead. This attribute is enabled
           by default.
    \value AA_UseHighDpiPixmaps Make QIcon::pixmap() generate high-dpi pixmaps
           that can be larger than the requested size. Such pixmaps will have
           \l {QPixmap::devicePixelRatio}{devicePixelRatio()} set to a value higher than 1.
           After setting this attribute, application code that uses pixmap
           sizes in layout geometry calculations should typically divide by
           \l {QPixmap::devicePixelRatio}{devicePixelRatio()} to get device-independent layout geometry.
    \value AA_ForceRasterWidgets Make top-level widgets use pure raster surfaces,
           and do not support non-native GL-based child widgets.
    \value AA_UseDesktopOpenGL Forces the usage of desktop OpenGL (for example,
           \e opengl32.dll or \e libGL.so) on platforms that use dynamic loading
           of the OpenGL implementation. This attribute must be set before
           QGuiApplication is constructed.
           This value was added in Qt 5.3.
    \value AA_UseOpenGLES Forces the usage of OpenGL ES 2.0 or higher on
           platforms that use dynamic loading of the OpenGL implementation.
           This attribute must be set before QGuiApplication is constructed.
           This value was added in Qt 5.3.
    \value AA_UseSoftwareOpenGL Forces the usage of a software based OpenGL
           implementation on platforms that use dynamic loading of the OpenGL
           implementation. This will typically be a patched build of
           \l{http://www.mesa3d.org/llvmpipe.html}{Mesa llvmpipe}, providing
           OpenGL 2.1. The value may have no effect if no such OpenGL
           implementation is available. The default name of this library is
           \c opengl32sw.dll and can be overridden by setting the environment
           variable \e QT_OPENGL_DLL. See the platform-specific pages, for
           instance \l{Qt for Windows}, for more information. This attribute
           must be set before QGuiApplication is constructed.
           This value was added in Qt 5.4.
    \value AA_ShareOpenGLContexts Enables resource sharing between the OpenGL
           contexts used by classes like QOpenGLWidget and QQuickWidget. This
           allows sharing OpenGL resources, like textures, between QOpenGLWidget
           instances that belong to different top-level windows. This attribute
           must be set before QGuiApplication is constructed.
           This value was added in Qt 5.4.
    \value AA_SetPalette Indicates whether a palette was explicitly set on the
           QGuiApplication. This value was added in Qt 5.5.
    \value AA_EnableHighDpiScaling Enables high-DPI scaling in Qt on supported
           platforms (see also \l{High DPI Displays}). Supported platforms are
           X11, Windows and Android. Enabling makes Qt scale the main (device
           independent) coordinate system according to display scale factors
           provided by the operating system. This corresponds to setting the
           QT_AUTO_SCREEN\unicode{0x200b}_SCALE_FACTOR environment variable to
           1. This attribute must be set before QGuiApplication is constructed.
           This value was added in Qt 5.6.
    \value AA_DisableHighDpiScaling Disables high-DPI scaling in Qt, exposing window
           system coordinates. Note that the window system may do its own scaling,
           so this does not guarantee that QPaintDevice::devicePixelRatio() will
           be equal to 1. In addition, scale factors set by QT_SCALE_FACTOR will not
           be affected. This corresponds to setting the
           QT_AUTO_SCREEN\unicode{0x200b}_SCALE_FACTOR environment variable to 0.
           This attribute must be set before QGuiApplication is constructed.
           This value was added in Qt 5.6.
    \value AA_UseStyleSheetPropagationInWidgetStyles By default, Qt Style Sheets
           disable regular QWidget palette and font propagation. When this flag
           is enabled, font and palette changes propagate as though the user had
           manually called the corresponding QWidget methods. See
           \l{The Style Sheet Syntax#Inheritance}{The Style Sheet Syntax - Inheritance}
           for more details.
           This value was added in Qt 5.7.
    \value AA_DontUseNativeDialogs All dialogs created while this attribute is
           set to true won't use the native dialogs provided by the platform.
           This value was added in Qt 5.7.
    \value AA_SynthesizeMouseForUnhandledTabletEvents All tablet events
           that are not accepted by the application will be translated
           to mouse events instead. This attribute is enabled
           by default.
           This value was added in Qt 5.7.
    \value AA_CompressHighFrequencyEvents Enables compression of certain frequent events.
           On the X11 windowing system, the default value is true, which means that
           QEvent::MouseMove, QEvent::TouchUpdate, and changes in window size and
           position will be combined whenever they occur more frequently than the
           application handles them, so that they don't accumulate and overwhelm the
           application later.
           On Windows 8 and above the default value is also true, but it only applies
           to touch events. Mouse and window events remain unaffected by this flag.
           On other platforms, the default is false.
           (In the future, the compression feature may be implemented across platforms.)
           You can test the attribute to see whether compression is enabled.
           If your application needs to handle all events with no compression,
           you can unset this attribute. Notice that input events from tablet devices
           will not be compressed. See AA_CompressTabletEvents if you want these to be
           compressed as well.
           This value was added in Qt 5.7.
    \value AA_CompressTabletEvents Enables compression of input events from tablet devices.
           Notice that AA_CompressHighFrequencyEvents must be true for events compression
           to be enabled, and that this flag extends the former to tablet events.
           Currently supported on the X11 windowing system, Windows 8 and above.
           The default value is false.
           This value was added in Qt 5.10.
    \value AA_DontCheckOpenGLContextThreadAffinity When making a context
           current using QOpenGLContext, do not check that the
           \l{QObject#Thread Affinity}{QObject thread affinity}
           of the QOpenGLContext object is the same thread calling
           \l{QOpenGLContext::makeCurrent}{makeCurrent()}.
           This value was added in Qt 5.8.
    \value AA_DisableShaderDiskCache Disables caching of shader program binaries
           on disk. By default Qt Quick, QPainter's OpenGL backend, and any
           application using QOpenGLShaderProgram with one of its
           \e addCacheableShaderFromSource overloads will employ a disk-based
           \l{Caching Program Binaries}{program binary cache} in either the shared
           or per-process cache storage location, on systems that support
           \e glProgramBinary(). In the unlikely event of this being problematic,
           set this attribute to disable all disk-based caching of shaders.
    \value AA_DisableWindowContextHelpButton Disables the WindowContextHelpButtonHint
           by default on Qt::Sheet and Qt::Dialog widgets. This hides the \gui ? button
           on Windows, which only makes sense if you use \l QWhatsThis functionality.
           This value was added in Qt 5.10. In Qt 6, WindowContextHelpButtonHint
           will not be set by default.
    The following values are deprecated or obsolete:
    \value AA_ImmediateWidgetCreation This attribute is no longer fully
           supported in Qt 5. It ensures that widgets are created
           as soon as they are constructed. By default, resources for
           widgets are allocated on demand to improve efficiency and
           minimize resource usage. Setting or clearing this attribute
           affects widgets constructed after the change. Setting it
           tells Qt to create toplevel windows immediately.
           Therefore, if it is important to minimize resource
           consumption, do not set this attribute.
    \value AA_MacPluginApplication This attribute has been deprecated.
           Use AA_PluginApplication instead.
    \value AA_MSWindowsUseDirect3DByDefault This value is obsolete and
           has no effect.
    \value AA_X11InitThreads This value is obsolete and has no effect.
    \omitvalue AA_AttributeCount
*/
/*!
    \enum Qt::MouseButton
    This enum type describes the different mouse buttons.
    \value NoButton        The button state does not refer to any
           button (see QMouseEvent::button()).
    \value AllButtons      This value corresponds to a mask of all
           possible mouse buttons. Use to set the 'acceptedButtons'
           property of a MouseArea to accept ALL mouse buttons.
    \value LeftButton      The left button is pressed, or an event refers
           to the left button. (The left button may be the right button on
           left-handed mice.)
    \value RightButton     The right button.
    \value MidButton       The middle button.
    \value MiddleButton    The middle button.
    \value BackButton      The 'Back' button. (Typically present on
           the 'thumb' side of a mouse with extra buttons. This is NOT
           the tilt wheel.)
    \value XButton1        The 'Back' Button.
    \value ExtraButton1    The 'Back' Button.
    \value ForwardButton   The 'Forward' Button. (Typically present
           beside the 'Back' button, and also pressed by the thumb.)
    \value XButton2        The 'Forward Button.
    \value ExtraButton2    The 'Forward' Button.
    \value TaskButton      The 'Task' Button.
    \value ExtraButton3    The 'Task' Button.
    \value ExtraButton4    The 7th non-wheel Mouse Button.
    \value ExtraButton5    The 8th non-wheel Mouse Button.
    \value ExtraButton6    The 9th non-wheel Mouse Button.
    \value ExtraButton7    The 10th non-wheel Mouse Button.
    \value ExtraButton8    The 11th non-wheel Mouse Button.
    \value ExtraButton9    The 12th non-wheel Mouse Button.
    \value ExtraButton10   The 13th non-wheel Mouse Button.
    \value ExtraButton11   The 14th non-wheel Mouse Button.
    \value ExtraButton12   The 15th non-wheel Mouse Button.
    \value ExtraButton13   The 16th non-wheel Mouse Button.
    \value ExtraButton14   The 17th non-wheel Mouse Button.
    \value ExtraButton15   The 18th non-wheel Mouse Button.
    \value ExtraButton16   The 19th non-wheel Mouse Button.
    \value ExtraButton17   The 20th non-wheel Mouse Button.
    \value ExtraButton18   The 21st non-wheel Mouse Button.
    \value ExtraButton19   The 22nd non-wheel Mouse Button.
    \value ExtraButton20   The 23rd non-wheel Mouse Button.
    \value ExtraButton21   The 24th non-wheel Mouse Button.
    \value ExtraButton22   The 25th non-wheel Mouse Button.
    \value ExtraButton23   The 26th non-wheel Mouse Button.
    \value ExtraButton24   The 27th non-wheel Mouse Button.
    \omitvalue MaxMouseButton
    \omitvalue MouseButtonMask
    \note Some models of multi-button mice are pre-configured with
    high-numbered Buttons emulating keyboard sequences, for use in
    specific games. In order for these Buttons to be seen as
    actual 'Mouse Buttons', the device must be re-configured (using
    the vendor's configuration tool).
    \sa KeyboardModifier, Modifier
*/
/*!
    \enum Qt::KeyboardModifier
    This enum describes the modifier keys.
    \value NoModifier       No modifier key is pressed.
    \value ShiftModifier    A Shift key on the keyboard is pressed.
    \value ControlModifier  A Ctrl key on the keyboard is pressed.
    \value AltModifier      An Alt key on the keyboard is pressed.
    \value MetaModifier     A Meta key on the keyboard is pressed.
    \value KeypadModifier   A keypad button is pressed.
    \value GroupSwitchModifier X11 only (unless activated on Windows by a command line argument).
                            A Mode_switch key on the keyboard is pressed.
    \omitvalue KeyboardModifierMask
    \note On \macos, the \c ControlModifier value corresponds to
    the Command keys on the keyboard, and the \c MetaModifier value
    corresponds to the Control keys. The \c KeypadModifier value will also be set
    when an arrow key is pressed as the arrow keys are considered part of the
    keypad.
    \note On Windows Keyboards, Qt::MetaModifier and Qt::Key_Meta are mapped
    to the Windows key.
    \sa MouseButton, Modifier
*/
/*!
    \enum Qt::Modifier
    This enum provides shorter names for the keyboard modifier keys
    supported by Qt.
    \note On \macos, the \c CTRL value corresponds to
    the Command keys on the keyboard, and the \c META value
    corresponds to the Control keys.
    \value SHIFT The Shift keys provided on all standard keyboards.
    \value META The Meta keys.
    \value CTRL The Ctrl keys.
    \value ALT The normal Alt keys, but not keys like AltGr.
    \value UNICODE_ACCEL The shortcut is specified as a Unicode code
    point, not as a Qt Key.
    \omitvalue MODIFIER_MASK
    \sa KeyboardModifier, MouseButton
*/
/*!
    \enum Qt::GlobalColor
    Qt's predefined QColor objects:
    \value white       \span {id="color-white"} {White (#ffffff) }
    \value black       \span {id="color-black"} {Black (#000000) }
    \value red         \span {id="color-red"} {Red (#ff0000) }
    \value darkRed     \span {id="color-darkRed"} {Dark red (#800000) }
    \value green       \span {id="color-green"} {Green (#00ff00) }
    \value darkGreen   \span {id="color-darkGreen"} {Dark green (#008000) }
    \value blue        \span {id="color-blue"} {Blue (#0000ff) }
    \value darkBlue    \span {id="color-darkBlue"} {Dark blue (#000080) }
    \value cyan        \span {id="color-cyan"} {Cyan (#00ffff) }
    \value darkCyan    \span {id="color-darkCyan"} {Dark cyan (#008080) }
    \value magenta     \span {id="color-magenta"} {Magenta (#ff00ff) }
    \value darkMagenta \span {id="color-darkMagenta"} {Dark magenta (#800080) }
    \value yellow      \span {id="color-yellow"} {Yellow (#ffff00) }
    \value darkYellow  \span {id="color-darkYellow"} {Dark yellow (#808000) }
    \value gray        \span {id="color-gray"} {Gray (#a0a0a4) }
    \value darkGray    \span {id="color-darkGray"} {Dark gray (#808080) }
    \value lightGray   \span {id="color-lightGray"} {Light gray (#c0c0c0) }
    \value transparent a transparent black value (i.e., QColor(0, 0, 0, 0))
    \value color0 0 pixel value (for bitmaps)
    \value color1 1 pixel value (for bitmaps)
    \sa QColor
*/
/*!
    \enum Qt::PenStyle
    This enum type defines the pen styles that can be drawn using
    QPainter. The styles are:
    \table
    \row
    \li \inlineimage qpen-solid.png
    \li \inlineimage qpen-dash.png
    \li \inlineimage qpen-dot.png
    \row
    \li Qt::SolidLine
    \li Qt::DashLine
    \li Qt::DotLine
    \row
    \li \inlineimage qpen-dashdot.png
    \li \inlineimage qpen-dashdotdot.png
    \li \inlineimage qpen-custom.png
    \row
    \li Qt::DashDotLine
    \li Qt::DashDotDotLine
    \li Qt::CustomDashLine
    \endtable
    \value NoPen  no line at all. For example, QPainter::drawRect()
    fills but does not draw any boundary line.
    \value SolidLine  A plain line.
    \value DashLine  Dashes separated by a few pixels.
    \value DotLine  Dots separated by a few pixels.
    \value DashDotLine  Alternate dots and dashes.
    \value DashDotDotLine  One dash, two dots, one dash, two dots.
    \value CustomDashLine  A custom pattern defined using
                           QPainterPathStroker::setDashPattern().
    \omitvalue MPenStyle
    \sa QPen
*/
/*!
    \enum Qt::PenCapStyle
    This enum type defines the pen cap styles supported by Qt, i.e.
    the line end caps that can be drawn using QPainter.
    \table
    \row
    \li \inlineimage qpen-square.png
    \li \inlineimage qpen-flat.png
    \li \inlineimage qpen-roundcap.png
    \row
    \li Qt::SquareCap
    \li Qt::FlatCap
    \li Qt::RoundCap
    \endtable
    \value FlatCap  a square line end that does not cover the end
        point of the line.
    \value SquareCap  a square line end that covers the end point and
        extends beyond it by half the line width.
    \value RoundCap  a rounded line end.
    \omitvalue MPenCapStyle
    \sa QPen
*/
/*!
    \enum Qt::PenJoinStyle
    This enum type defines the pen join styles supported by Qt, i.e.
    which joins between two connected lines can be drawn using
    QPainter.
    \table
    \row
    \li \inlineimage qpen-bevel.png
    \li \inlineimage qpen-miter.png
    \li \inlineimage qpen-roundjoin.png
    \row
    \li Qt::BevelJoin
    \li Qt::MiterJoin
    \li Qt::RoundJoin
    \endtable
    \value MiterJoin  The outer edges of the lines are extended to
           meet at an angle, and this area is filled.
    \value BevelJoin  The triangular notch between the two lines is filled.
    \value RoundJoin  A circular arc between the two lines is filled.
    \value SvgMiterJoin A miter join corresponding to the definition of
           a miter join in the \l{http://www.w3.org/TR/SVGMobile12/}{SVG 1.2 Tiny} specification.
    \omitvalue MPenJoinStyle
    \sa QPen
*/
/*!
    \enum Qt::BrushStyle
    This enum type defines the brush styles supported by Qt, i.e. the
    fill pattern of shapes drawn using QPainter.
    \image brush-styles.png Brush Styles
    \value NoBrush  No brush pattern.
    \value SolidPattern  Uniform color.
    \value Dense1Pattern  Extremely dense brush pattern.
    \value Dense2Pattern  Very dense brush pattern.
    \value Dense3Pattern  Somewhat dense brush pattern.
    \value Dense4Pattern  Half dense brush pattern.
    \value Dense5Pattern  Somewhat sparse brush pattern.
    \value Dense6Pattern  Very sparse brush pattern.
    \value Dense7Pattern  Extremely sparse brush pattern.
    \value HorPattern  Horizontal lines.
    \value VerPattern  Vertical lines.
    \value CrossPattern  Crossing horizontal and vertical lines.
    \value BDiagPattern  Backward diagonal lines.
    \value FDiagPattern  Forward diagonal lines.
    \value DiagCrossPattern  Crossing diagonal lines.
    \value LinearGradientPattern  Linear gradient (set using a dedicated QBrush constructor).
    \value ConicalGradientPattern  Conical gradient (set using a dedicated QBrush constructor).
    \value RadialGradientPattern  Radial gradient (set using a dedicated QBrush constructor).
    \value TexturePattern  Custom pattern (see QBrush::setTexture()).
    \sa QBrush
*/
/*!
    \enum Qt::TextFlag
    This enum type is used to define some modifier flags. Some of
    these flags only make sense in the context of printing:
    \value TextSingleLine Treats all whitespace as spaces and prints just
           one line.
    \value TextDontClip If it's impossible to stay within the given bounds,
           it prints outside.
    \value TextExpandTabs Makes the U+0009 (ASCII tab) character move to
           the next tab stop.
    \value TextShowMnemonic Displays the string "\&P" as \underline{P}
           For an ampersand, use "\&\&".
    \value TextWordWrap Breaks lines at appropriate points, e.g. at word
           boundaries.
    \value TextWrapAnywhere Breaks lines anywhere, even within words.
    \value TextHideMnemonic Same as Qt::TextShowMnemonic but doesn't draw
           the underlines.
    \value TextDontPrint Treat this text as "hidden" and don't print it.
    \value TextIncludeTrailingSpaces When this option is set,
           QTextLine::naturalTextWidth() and QTextLine::naturalTextRect() will
           return a value that includes the width of trailing spaces in the
           text; otherwise this width is excluded.
    \value TextJustificationForced Ensures that text lines are justified.
    \omitvalue TextLongestVariant
    \omitvalue TextBypassShaping
    \omitvalue TextForceLeftToRight
    \omitvalue TextForceRightToLeft
    You can use as many modifier flags as you want, except that
    Qt::TextSingleLine and Qt::TextWordWrap cannot be combined.
    Flags that are inappropriate for a given use are generally
    ignored.
*/
/*!
    \enum Qt::BGMode
    Background mode:
    \value TransparentMode
    \value OpaqueMode
*/
/*!
    \enum Qt::ConnectionType
    This enum describes the types of connection that can be used
    between signals and slots. In particular, it determines whether a
    particular signal is delivered to a slot immediately or queued for
    delivery at a later time.
    \value AutoConnection
           \b (Default) If the receiver \l{QObject#Thread Affinity}{lives in} the
           thread that emits the signal, Qt::DirectConnection is used. Otherwise,
           Qt::QueuedConnection is used. The connection type is
           determined when the signal is emitted.
    \value DirectConnection
           The slot is invoked immediately when the signal is
           emitted. The slot is executed in the signalling thread.
    \value QueuedConnection
           The slot is invoked when control returns to the event loop
           of the receiver's thread. The slot is executed in the
           receiver's thread.
    \value BlockingQueuedConnection
           Same as Qt::QueuedConnection, except that the signalling thread blocks
           until the slot returns. This connection must \e not be used if the
           receiver lives in the signalling thread, or else the application
           will deadlock.
    \value UniqueConnection
           This is a flag that can be combined with any one of the above
           connection types, using a bitwise OR. When Qt::UniqueConnection is
           set, QObject::connect() will fail if the connection already exists
           (i.e. if the same signal is already connected to the same slot
           for the same pair of objects). This flag was introduced in Qt 4.6.
    With queued connections, the parameters must be of types that are
    known to Qt's meta-object system, because Qt needs to copy the
    arguments to store them in an event behind the scenes. If you try
    to use a queued connection and get the error message:
    \snippet code/doc_src_qnamespace.qdoc 0
    Call qRegisterMetaType() to register the data type before you
    establish the connection.
    When using signals and slots with multiple threads, see \l{Signals and Slots Across Threads}.
    \sa {Thread Support in Qt}, QObject::connect(), qRegisterMetaType(), Q_DECLARE_METATYPE()
*/
/*!
    \enum Qt::DateFormat
    \value TextDate The default Qt format, which includes the day and month name,
    the day number in the month, and the year in full. The day and month names will
    be short, localized names. This is basically equivalent to using the date format
    string, "ddd MMM d yyyy". See QDate::toString() for more information.
    \value ISODate \l{ISO 8601} extended format: either \c{yyyy-MM-dd} for dates or
    \c{yyyy-MM-ddTHH:mm:ss} (e.g. 2017-07-24T15:46:29), or with a time-zone
    suffix (Z for UTC otherwise an offset as [+|-]HH:mm) where appropriate
    for combined dates and times.
    \value ISODateWithMs \l{ISO 8601} extended format, including milliseconds if applicable.
    \value SystemLocaleShortDate The \l{QLocale::ShortFormat}{short format} used
    by the \l{QLocale::system()}{operating system}.
    \value SystemLocaleLongDate The \l{QLocale::LongFormat}{long format} used
    by the \l{QLocale::system()}{operating system}.
    \value DefaultLocaleShortDate The \l{QLocale::ShortFormat}{short format} specified
    by the \l{QLocale::setDefault()}{application's locale}.
    \value DefaultLocaleLongDate The \l{QLocale::LongFormat}{long format} used
    by the \l{QLocale::setDefault()}{application's locale}.
    \value SystemLocaleDate \e{This enum value is deprecated.} Use Qt::SystemLocaleShortDate
    instead (or Qt::SystemLocaleLongDate if you want long dates).
    \value LocaleDate \e{This enum value is deprecated.} Use Qt::DefaultLocaleShortDate
    instead (or Qt::DefaultLocaleLongDate if you want long dates).
    \value LocalDate \e{This enum value is deprecated.} Use Qt::SystemLocaleShortDate
    instead (or Qt::SystemLocaleLongDate if you want long dates).
    \value RFC2822Date \l{RFC 2822}, \l{RFC 850} and \l{RFC 1036} format: either
    \c{[ddd,] dd MMM yyyy hh:mm[:ss] +/-TZ} or \c{ddd MMM dd yyyy hh:mm[:ss] +/-TZ}
    for combined dates and times.
    \note For \c ISODate formats, each \c Y, \c M and \c D represents a single digit
    of the year, month and day used to specify the date. Each \c H, \c M and \c S
    represents a single digit of the hour, minute and second used to specify the time.
    The presence of a literal \c T character is used to separate the date and time when
    both are specified.
*/
/*!
    \enum Qt::TimeSpec
    \value LocalTime Locale dependent time (Timezones and Daylight Savings Time).
    \value UTC Coordinated Universal Time, replaces Greenwich Mean Time.
    \value OffsetFromUTC An offset in seconds from Coordinated Universal Time.
    \value TimeZone A named time zone using a specific set of Daylight Savings rules.
*/
/*!
    \enum Qt::DayOfWeek
    \value Monday
    \value Tuesday
    \value Wednesday
    \value Thursday
    \value Friday
    \value Saturday
    \value Sunday
*/
/*!
    \enum Qt::CaseSensitivity
    \value CaseInsensitive
    \value CaseSensitive
*/
/*!
    \enum Qt::ToolBarArea
    \value LeftToolBarArea
    \value RightToolBarArea
    \value TopToolBarArea
    \value BottomToolBarArea
    \value AllToolBarAreas
    \value NoToolBarArea
    \omitvalue ToolBarArea_Mask
*/
/*!
    \enum Qt::DockWidgetArea
    \value LeftDockWidgetArea
    \value RightDockWidgetArea
    \value TopDockWidgetArea
    \value BottomDockWidgetArea
    \value AllDockWidgetAreas
    \value NoDockWidgetArea
    \omitvalue DockWidgetArea_Mask
*/
/*!
    \enum Qt::ImageConversionFlag
    The options marked "(default)" are set if no other values from
    the list are included (since the defaults are zero):
    Color/Mono preference (ignored for QBitmap):
    \value AutoColor (default) - If the image has \l{QImage::depth()}{depth} 1 and contains only
           black and white pixels, the pixmap becomes monochrome.
    \value ColorOnly The pixmap is dithered/converted to the
           \l{QPixmap::defaultDepth()}{native display depth}.
    \value MonoOnly The pixmap becomes monochrome. If necessary,
           it is dithered using the chosen dithering algorithm.
    Dithering mode preference:
    \value DiffuseDither (default) - A high-quality dither using error diffusion.
    \value OrderedDither A faster, ordered dither.
    \value ThresholdDither No dithering; closest color is used.
    Dithering mode preference for 1-bit alpha masks:
    \value ThresholdAlphaDither (default) - No dithering.
    \value OrderedAlphaDither A faster, ordered dither.
    \value DiffuseAlphaDither A high-quality dither using error diffusion.
    \omitvalue NoAlpha
    Color matching versus dithering preference:
    \value PreferDither Always dither images when converting to smaller color-spaces.
    \value AvoidDither Only dither to indexed formats if the source image uses more
           different colors than the size of the color table of the destination format.
    \value AutoDither (default) - Only dither when down-converting to 1 or 8-bit indexed formats.
    \omitvalue ColorMode_Mask
    \omitvalue Dither_Mask
    \omitvalue AlphaDither_Mask
    \omitvalue DitherMode_Mask
    \value NoOpaqueDetection Do not check whether the image contains non-opaque
           pixels. Use this if you know that the image is semi-transparent and
           you want to avoid the overhead of checking the pixels in the image
           until a non-opaque pixel is found, or if you want the pixmap to
           retain an alpha channel for some other reason. If the image has no
           alpha channel this flag has no effect.
    \value NoFormatConversion Don't do any format conversions on the image.
           Can be useful when converting a QImage to a QPixmap for a one-time
           rendering operation for example. Note that a QPixmap not in the
           preferred format will be much slower as a paint device.
*/
/*!
    \enum Qt::UIEffect
    This enum describes the available UI effects.
    By default, Qt will try to use the platform specific desktop
    settings for each effect. Use the
    QApplication::setDesktopSettingsAware() function (passing \c false
    as argument) to prevent this, and the
    QApplication::setEffectEnabled() to enable or disable a particular
    effect.
    Note that all effects are disabled on screens running at less than
    16-bit color depth.
    \omitvalue UI_General
    \value UI_AnimateMenu Show animated menus.
    \value UI_FadeMenu Show faded menus.
    \value UI_AnimateCombo Show animated comboboxes.
    \value UI_AnimateTooltip Show tooltip animations.
    \value UI_FadeTooltip Show tooltip fading effects.
    \value UI_AnimateToolBox Reserved
    \sa QApplication::setEffectEnabled(), QGuiApplication::setDesktopSettingsAware()
*/
/*! \enum Qt::AspectRatioMode
    This enum type defines what happens to the aspect ratio when
    scaling an rectangle.
    \image qimage-scaling.png
    \value IgnoreAspectRatio  The size is scaled freely. The aspect
                              ratio is not preserved.
    \value KeepAspectRatio  The size is scaled to a rectangle as
                            large as possible inside a given
                            rectangle, preserving the aspect ratio.
    \value KeepAspectRatioByExpanding  The size is scaled to a
                                       rectangle as small as possible
                                       outside a given rectangle,
                                       preserving the aspect ratio.
    \sa QSize::scale(), QImage::scaled()
*/
/*! \enum Qt::TransformationMode
    This enum type defines whether image transformations (e.g.,
    scaling) should be smooth or not.
    \value FastTransformation  The transformation is performed
                               quickly, with no smoothing.
    \value SmoothTransformation  The resulting image is transformed
                                 using bilinear filtering.
    \sa QImage::scaled()
*/
/*! \enum Qt::Axis
    This enum type defines three values to represent the three
    axes in the cartesian coordinate system.
    \value XAxis  The X axis.
    \value YAxis  The Y axis.
    \value ZAxis  The Z axis.
    \sa QTransform::rotate(), QTransform::rotateRadians()
 */
/*!
    \enum Qt::WidgetAttribute
    \keyword widget attributes
    This enum type is used to specify various widget attributes.
    Attributes are set and cleared with QWidget::setAttribute(), and
    queried with QWidget::testAttribute(), although some have special
    convenience functions which are mentioned below.
    \value WA_AcceptDrops Allows data from drag and drop operations
    to be dropped onto the widget (see QWidget::setAcceptDrops()).
    \value WA_AlwaysShowToolTips Enables tooltips for inactive windows.
    \value WA_ContentsPropagated This flag is superfluous and
    obsolete; it no longer has any effect. Since Qt 4.1, all widgets
    that do not set WA_PaintOnScreen propagate their contents.
    \value WA_CustomWhatsThis Indicates that the widget wants to
    continue operating normally in "What's This?" mode. This is set by the
    widget's author.
    \value WA_DeleteOnClose Makes Qt delete this widget when the
    widget has accepted the close event (see QWidget::closeEvent()).
    \value WA_Disabled Indicates that the widget is disabled, i.e.
    it does not receive any mouse or keyboard events. There is also a
    getter functions QWidget::isEnabled().  This is set/cleared by the
    Qt kernel.
    \value WA_DontShowOnScreen Indicates that the widget is hidden or is
    not a part of the viewable Desktop.
    \omitvalue WA_DropSiteRegistered
    \omitvalue WA_ForceAcceptDrops
    \value WA_ForceDisabled Indicates that the widget is
    explicitly disabled, i.e. it will remain disabled even when all
    its ancestors are set to the enabled state. This implies
    WA_Disabled. This is set/cleared by QWidget::setEnabled() and
    QWidget::setDisabled().
    \value WA_ForceUpdatesDisabled Indicates that updates are
    explicitly disabled for the widget; i.e. it will remain disabled
    even when all its ancestors are set to the updates-enabled state.
    This implies WA_UpdatesDisabled. This is set/cleared by
    QWidget::setUpdatesEnabled().
    \value WA_GroupLeader
        \e{This attribute has been deprecated.} Use QWidget::windowModality
        instead.
    \value WA_Hover Forces Qt to generate paint events when the mouse
    enters or leaves the widget. This feature is typically used when
    implementing custom styles; see the \l{widgets/styles}{Styles}
    example for details.
    \value WA_InputMethodEnabled Enables input methods for Asian languages.
    Must be set when creating custom text editing widgets.
    \value WA_KeyboardFocusChange Set on a toplevel window when
    the users changes focus with the keyboard (tab, backtab, or shortcut).
    \value WA_KeyCompression Enables key event compression if set,
    and disables it if not set. By default key compression is off, so
    widgets receive one key press event for each key press (or more,
    since autorepeat is usually on). If you turn it on and your
    program doesn't keep up with key input, Qt may try to compress key
    events so that more than one character can be processed in each
    event.
    For example, a word processor widget might receive 2, 3 or more
    characters in each QKeyEvent::text(), if the layout recalculation
    takes too long for the CPU.
    If a widget supports multiple character unicode input, it is
    always safe to turn the compression on.
    Qt performs key event compression only for printable characters.
    Qt::Modifier keys, cursor movement keys, function keys and
    miscellaneous action keys (e.g. Escape, Enter, Backspace,
    PrintScreen) will stop key event compression, even if there are
    more compressible key events available.
    Platforms other than Mac and X11 do not support this compression,
    in which case turning it on will have no effect.
    This is set/cleared by the widget's author.
    \value WA_LayoutOnEntireRect Indicates that the widget
    wants QLayout to operate on the entire QWidget::rect(), not only
    on QWidget::contentsRect(). This is set by the widget's author.
    \value WA_LayoutUsesWidgetRect Ignore the layout item rect from the style
    when laying out this widget with QLayout.
    \value WA_MacNoClickThrough This value is obsolete and has no effect.
    \value WA_MacOpaqueSizeGrip Indicates that the native Carbon size grip
    should be opaque instead of transparent (the default). This attribute
    is only applicable to \macos and is set by the widget's author.
    \value WA_MacShowFocusRect Indicates that this widget should get a
    QFocusFrame around it. Some widgets draw their own focus halo
    regardless of this attribute. Not that the QWidget::focusPolicy
    also plays the main role in whether something is given focus or
    not, this only controls whether or not this gets the focus
    frame. This attribute is only applicable to \macos.
    \value WA_MacNormalSize Indicates the widget should have the
    normal size for widgets in \macos. This attribute is only
    applicable to \macos.
    \value WA_MacSmallSize Indicates the widget should have the small
    size for widgets in \macos. This attribute is only applicable to
    \macos.
    \value WA_MacMiniSize Indicates the widget should have the mini
    size for widgets in \macos. This attribute is only applicable to
    \macos.
    \value WA_MacVariableSize Indicates the widget can choose between
    alternative sizes for widgets to avoid clipping.
    This attribute is only applicable to \macos.
    \value WA_MacBrushedMetal This value is obsolete and has no effect.
    \omitvalue WA_MacMetalStyle
    \value WA_Mapped Indicates that the widget is mapped on screen.
    This is set/cleared by the Qt kernel.
    \value WA_MouseNoMask Makes the widget receive mouse events for
    the entire widget regardless of the currently set mask,
    overriding QWidget::setMask(). This is not applicable for
    top-level windows.
    \value WA_MouseTracking Indicates that the widget has mouse
    tracking enabled. See QWidget::mouseTracking.
    \value WA_Moved Indicates that the widget has an explicit
    position. This is set/cleared by QWidget::move() and
    by QWidget::setGeometry().
    \value WA_MSWindowsUseDirect3D This value is obsolete and has no
    effect.
    \value WA_NoBackground This value is obsolete. Use
    WA_OpaquePaintEvent instead.
    \value WA_NoChildEventsForParent Indicates that the widget does
    not want ChildAdded or ChildRemoved events sent to its
    parent. This is rarely necessary but can help to avoid automatic
    insertion widgets like splitters and layouts. This is set by a
    widget's author.
    \value WA_NoChildEventsFromChildren Indicates that the widget does
    not want to receive ChildAdded or ChildRemoved events sent from its
    children. This is set by a widget's author.
    \value WA_NoMouseReplay Used for pop-up widgets. Indicates that the most
    recent mouse press event should not be replayed when the pop-up widget
    closes. The flag is set by the widget's author and cleared by the Qt kernel
    every time the widget receives a new mouse event.
    \value WA_NoMousePropagation Prohibits mouse events from being propagated
    to the widget's parent. This attribute is disabled by default.
    \value WA_TransparentForMouseEvents When enabled, this attribute disables
    the delivery of mouse events to the widget and its children. Mouse events
    are delivered to other widgets as if the widget and its children were not
    present in the widget hierarchy; mouse clicks and other events effectively
    "pass through" them. This attribute is disabled by default.
    \value WA_NoSystemBackground Indicates that the widget has no background,
    i.e. when the widget receives paint events, the background is not
    automatically repainted. \b Note: Unlike WA_OpaquePaintEvent, newly exposed
    areas are \b never filled with the background (e.g., after showing a
    window for the first time the user can see "through" it until the
    application processes the paint events). This flag is set or cleared by the
    widget's author.
    \value WA_OpaquePaintEvent Indicates that the widget paints all its pixels
    when it receives a paint event. Thus, it is not required for operations
    like updating, resizing, scrolling and focus changes to erase the widget
    before generating paint events. The use of WA_OpaquePaintEvent provides a
    small optimization by helping to reduce flicker on systems that do not
    support double buffering and avoiding computational cycles necessary to
    erase the background prior to painting. \b Note: Unlike
    WA_NoSystemBackground, WA_OpaquePaintEvent makes an effort to avoid
    transparent window backgrounds. This flag is set or cleared by the widget's
    author.
    \value WA_OutsideWSRange Indicates that the widget is outside
    the valid range of the window system's coordinate system. A widget
    outside the valid range cannot be mapped on screen. This is
    set/cleared by the Qt kernel.
    \value WA_PaintOnScreen Indicates that the widget wants to draw directly
    onto the screen. Widgets with this attribute set do not participate in
    composition management, i.e. they cannot be semi-transparent or shine
    through semi-transparent overlapping widgets. \b Note: This flag is only
    supported on X11 and it disables double buffering. On Qt for Embedded
    Linux, the flag only works when set on a top-level widget and it relies on
    support from the active screen driver. This flag is set or cleared by the
    widget's author. To render outside of Qt's paint system, e.g., if you
    require native painting primitives, you need to reimplement
    QWidget::paintEngine() to return 0 and set this flag.
    \value WA_PaintUnclipped Makes all painters operating on this widget
    unclipped. Children of this widget or other widgets in front of it do not
    clip the area the painter can paint on. This flag is only supported for
    widgets with the WA_PaintOnScreen flag set. The preferred way to do this in
    a cross platform way is to create a transparent widget that lies in front
    of the other widgets.
    \value WA_PendingMoveEvent Indicates that a move event is pending, e.g.,
    when a hidden widget was moved. This flag is set or cleared by the Qt
    kernel.
    \value WA_PendingResizeEvent Indicates that a resize event is pending,
    e.g., when a hidden widget was resized. This flag is set or cleared by the
    Qt kernel.
    \value WA_QuitOnClose Makes Qt quit the application when the last widget
    with the attribute set has accepted closeEvent(). This behavior can be
    modified with the QApplication::quitOnLastWindowClosed property. By default
    this attribute is set for all widgets of type Qt::Window.
    \value WA_Resized Indicates that the widget has an explicit size. This flag
    is set or cleared by QWidget::resize() and QWidget::setGeometry().
    \value WA_RightToLeft Indicates that the layout direction for the widget
    is right to left.
    \value WA_SetCursor Indicates that the widget has a cursor of its own. This
    flag is set or cleared by QWidget::setCursor() and QWidget::unsetCursor().
    \value WA_SetFont Indicates that the widget has a font of its own. This
    flag is set or cleared by QWidget::setFont().
    \value WA_SetPalette Indicates that the widget has a palette of its own.
    This flag is set or cleared by QWidget::setPalette().
    \value WA_SetStyle Indicates that the widget has a style of its own. This
    flag is set or cleared by QWidget::setStyle().
    \value WA_ShowModal \e{This attribute has been deprecated.} Use
    QWidget::windowModality instead.
    \value WA_StaticContents Indicates that the widget contents are north-west
    aligned and static. On resize, such a widget will receive paint events only
    for parts of itself that are newly visible. This flag is set or cleared by
    the widget's author.
    \value WA_StyleSheet Indicates that the widget is styled using a
    \l{Qt Style Sheets}{style sheet}. WA_StyleSheet is set whenever a widget
    is subject to a style sheet, even if the style sheet did not affect the
    widget appearance.
    \value WA_StyleSheetTarget Indicates that the widget appearance was modified
    by a \l{Qt Style Sheets}{style sheet}. WA_StyleSheet will also be set.
    \value WA_TabletTracking Indicates that the widget has tablet
    tracking enabled. See QWidget::tabletTracking.
    \value WA_TranslucentBackground Indicates that the widget should have a
    translucent background, i.e., any non-opaque regions of the widgets will be
    translucent because the widget will have an alpha channel. Setting this
    flag causes WA_NoSystemBackground to be set. On Windows the
    widget also needs the Qt::FramelessWindowHint window flag to be set.
    This flag is set or cleared by the widget's author.
    \value WA_UnderMouse Indicates that the widget is under the mouse cursor.
    The value is not updated correctly during drag and drop operations. There
    is also a getter function, QWidget::underMouse(). This flag is set or
    cleared by the Qt kernel.
    \value WA_UpdatesDisabled Indicates that updates are blocked (including the
    system background). This flag is set or cleared by the Qt kernel.
    \b Warning: This flag must \e never be set or cleared by the widget's author.
    \value WA_WindowModified Indicates that the window is marked as modified.
    On some platforms this flag will do nothing, on others (including \macos
    and Windows) the window will take a modified appearance. This flag is set
    or cleared by QWidget::setWindowModified().
    \value WA_WindowPropagation Makes a toplevel window inherit font, palette
    and locale from its parent.
    \value WA_MacAlwaysShowToolWindow On \macos, show the tool window even
    when the application is not active.  By default, all tool windows are
    hidden when the application is inactive.
    \value WA_SetLocale Indicates the locale should be taken into consideration
    in the widget.
    \value WA_StyledBackground Indicates the widget should be drawn using a
    styled background.
    \value WA_ShowWithoutActivating Show the widget without making it active.
    \value WA_NativeWindow Indicates that a native window is created for the
    widget. Enabling this flag will also force a native window for the widget's
    ancestors unless Qt::WA_DontCreateNativeAncestors is set.
    \value WA_DontCreateNativeAncestors Indicates that the widget's ancestors
    are kept non-native even though the widget itself is native.
    \value WA_X11NetWmWindowTypeDesktop Adds _NET_WM_WINDOW_TYPE_DESKTOP to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms.
    \value WA_X11NetWmWindowTypeDock Adds _NET_WM_WINDOW_TYPE_DOCK to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms.
    \value WA_X11NetWmWindowTypeToolBar Adds _NET_WM_WINDOW_TYPE_TOOLBAR to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for QToolBar.
    \value WA_X11NetWmWindowTypeMenu Adds _NET_WM_WINDOW_TYPE_MENU to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for QMenu when torn-off.
    \value WA_X11NetWmWindowTypeUtility Adds _NET_WM_WINDOW_TYPE_UTILITY to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for the Qt::Tool window type.
    \value WA_X11NetWmWindowTypeSplash Adds _NET_WM_WINDOW_TYPE_SPLASH to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for the Qt::SplashScreen window type.
    \value WA_X11NetWmWindowTypeDialog Adds _NET_WM_WINDOW_TYPE_DIALOG
    to the window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This
    attribute has no effect on non-X11 platforms. \b Note: Qt automatically sets
    this attribute for the Qt::Dialog and Qt::Sheet window types.
    \value WA_X11NetWmWindowTypeDropDownMenu Adds
    _NET_WM_WINDOW_TYPE_DROPDOWN_MENU to the window's
    _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This
    attribute has no effect on non-X11 platforms. \b Note: Qt
    automatically sets this attribute for QMenu objects added to a QMenuBar.
    \value WA_X11NetWmWindowTypePopupMenu Adds _NET_WM_WINDOW_TYPE_POPUP_MENU
    to the window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for QMenu.
    \value WA_X11NetWmWindowTypeToolTip Adds _NET_WM_WINDOW_TYPE_TOOLTIP to the
    window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for the Qt::ToolTip window type.
    \value WA_X11NetWmWindowTypeNotification Adds
    _NET_WM_WINDOW_TYPE_NOTIFICATION to the window's _NET_WM_WINDOW_TYPE X11
    window property. See http://standards.freedesktop.org/wm-spec/ for more
    details. This attribute has no effect on non-X11 platforms.
    \value WA_X11NetWmWindowTypeCombo Adds _NET_WM_WINDOW_TYPE_COMBO
    to the window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute for the QComboBox pop-up.
    \value WA_X11NetWmWindowTypeDND Adds _NET_WM_WINDOW_TYPE_DND to
    the window's _NET_WM_WINDOW_TYPE X11 window property. See
    http://standards.freedesktop.org/wm-spec/ for more details. This attribute
    has no effect on non-X11 platforms. \b Note: Qt automatically sets this
    attribute on the feedback widget used during a drag.
    \value WA_MacFrameworkScaled This value is obsolete and has no effect.
    \value WA_AcceptTouchEvents Allows touch events (see QTouchEvent)
    to be sent to the widget. Must be set on all widgets that can
    handle touch events. Without this attribute set, events from a
    touch device will be sent as mouse events.
    \value WA_TouchPadAcceptSingleTouchEvents Allows touchpad single
    touch events to be sent to the widget.
    \value WA_X11DoNotAcceptFocus Asks the window manager to not give focus
    to this top level window. This attribute has no effect on non-X11
    platforms.
    \value WA_AlwaysStackOnTop Since Qt 5.4, this value forces QOpenGLWidget and
    QQuickWidget to be drawn last, on top of other widgets. Ignored for other
    type of widgets. Setting this attribute breaks the stacking order, but
    allows having a semi-transparent OpenGL widget with other widgets visible
    underneath. It is strongly recommended to call update() on the widget's
    top-level window after enabling or disabling this attribute.
    \omitvalue WA_SetLayoutDirection
    \omitvalue WA_InputMethodTransparent
    \omitvalue WA_WState_CompressKeys
    \omitvalue WA_WState_ConfigPending
    \omitvalue WA_WState_Created
    \omitvalue WA_WState_DND
    \omitvalue WA_WState_ExplicitShowHide
    \omitvalue WA_WState_Hidden
    \omitvalue WA_WState_InPaintEvent
    \omitvalue WA_WState_OwnSizePolicy
    \omitvalue WA_WState_Polished
    \omitvalue WA_WState_Reparented
    \omitvalue WA_WState_Visible
    \omitvalue WA_SetWindowIcon
    \omitvalue WA_PendingUpdate
    \omitvalue WA_LaidOut
    \omitvalue WA_GrabbedShortcut
    \omitvalue WA_DontShowOnScreen
    \omitvalue WA_InvalidSize
    \omitvalue WA_ForceUpdatesDisabled
    \omitvalue WA_NoX11EventCompression
    \omitvalue WA_TintedBackground
    \omitvalue WA_X11OpenGLOverlay
    \omitvalue WA_CanHostQMdiSubWindowTitleBar
    \omitvalue WA_AttributeCount
    \omitvalue WA_StyleSheet
    \omitvalue WA_X11BypassTransientForHint
    \omitvalue WA_SetWindowModality
    \omitvalue WA_WState_WindowOpacitySet
    \omitvalue WA_WState_AcceptedTouchBeginEvent
    \omitvalue WA_MacNoShadow
    \value WA_ContentsMarginsRespectsSafeArea A QWidget respects the safe
    area margins of a window by incorporating the margins into its contents'
    margins by default. This means, that a QLayout will use the content area
    of a widget for its layout, unless the Qt::WA_LayoutOnEntireRect attribute
    is set. This along with a contents margin of 0 can be used on the actual
    layout, to allow for example a background image to underlay the status bar and other
    system areas on an iOS device, while still allowing child widgets of
    that background to be inset based on the safe area.
*/
/*! \typedef Qt::HANDLE
    A handle type for system objects, defined as \c{void *}
    on all platforms.
*/
/*!
    \enum Qt::Key
    The key names used by Qt.
    \value Key_Escape
    \value Key_Tab
    \value Key_Backtab
    \value Key_Backspace
    \value Key_Return
    \value Key_Enter     Typically located on the keypad.
    \value Key_Insert
    \value Key_Delete
    \value Key_Pause    The Pause/Break key (\b Note: Not related to pausing media)
    \value Key_Print
    \value Key_SysReq
    \value Key_Clear    Corresponds to the \b Clear key on selected Apple
                        keyboard models. On other systems it is commonly mapped
                        to the numeric keypad key \b 5, when \b {Num Lock} is
                        \c off.
    \value Key_Home
    \value Key_End
    \value Key_Left
    \value Key_Up
    \value Key_Right
    \value Key_Down
    \value Key_PageUp
    \value Key_PageDown
    \value Key_Shift
    \value Key_Control    On \macos, this corresponds to the Command keys.
    \value Key_Meta       On \macos, this corresponds to the Control keys.
                          On Windows keyboards, this key is mapped to the
                          Windows key.
    \value Key_Alt
    \value Key_AltGr      On Windows, when the KeyDown event for this key is
                          sent, the Ctrl+Alt modifiers are also set.
    \value Key_CapsLock
    \value Key_NumLock
    \value Key_ScrollLock
    \value Key_F1
    \value Key_F2
    \value Key_F3
    \value Key_F4
    \value Key_F5
    \value Key_F6
    \value Key_F7
    \value Key_F8
    \value Key_F9
    \value Key_F10
    \value Key_F11
    \value Key_F12
    \value Key_F13
    \value Key_F14
    \value Key_F15
    \value Key_F16
    \value Key_F17
    \value Key_F18
    \value Key_F19
    \value Key_F20
    \value Key_F21
    \value Key_F22
    \value Key_F23
    \value Key_F24
    \value Key_F25
    \value Key_F26
    \value Key_F27
    \value Key_F28
    \value Key_F29
    \value Key_F30
    \value Key_F31
    \value Key_F32
    \value Key_F33
    \value Key_F34
    \value Key_F35
    \value Key_Super_L
    \value Key_Super_R
    \value Key_Menu
    \value Key_Hyper_L
    \value Key_Hyper_R
    \value Key_Help
    \value Key_Direction_L
    \value Key_Direction_R
    \value Key_Space
    \value Key_Any
    \value Key_Exclam
    \value Key_QuoteDbl
    \value Key_NumberSign
    \value Key_Dollar
    \value Key_Percent
    \value Key_Ampersand
    \value Key_Apostrophe
    \value Key_ParenLeft
    \value Key_ParenRight
    \value Key_Asterisk
    \value Key_Plus
    \value Key_Comma
    \value Key_Minus
    \value Key_Period
    \value Key_Slash
    \value Key_0
    \value Key_1
    \value Key_2
    \value Key_3
    \value Key_4
    \value Key_5
    \value Key_6
    \value Key_7
    \value Key_8
    \value Key_9
    \value Key_Colon
    \value Key_Semicolon
    \value Key_Less
    \value Key_Equal
    \value Key_Greater
    \value Key_Question
    \value Key_At
    \value Key_A
    \value Key_B
    \value Key_C
    \value Key_D
    \value Key_E
    \value Key_F
    \value Key_G
    \value Key_H
    \value Key_I
    \value Key_J
    \value Key_K
    \value Key_L
    \value Key_M
    \value Key_N
    \value Key_O
    \value Key_P
    \value Key_Q
    \value Key_R
    \value Key_S
    \value Key_T
    \value Key_U
    \value Key_V
    \value Key_W
    \value Key_X
    \value Key_Y
    \value Key_Z
    \value Key_BracketLeft
    \value Key_Backslash
    \value Key_BracketRight
    \value Key_AsciiCircum
    \value Key_Underscore
    \value Key_QuoteLeft
    \value Key_BraceLeft
    \value Key_Bar
    \value Key_BraceRight
    \value Key_AsciiTilde
    \value Key_nobreakspace
    \value Key_exclamdown
    \value Key_cent
    \value Key_sterling
    \value Key_currency
    \value Key_yen
    \value Key_brokenbar
    \value Key_section
    \value Key_diaeresis
    \value Key_copyright
    \value Key_ordfeminine
    \value Key_guillemotleft
    \value Key_notsign
    \value Key_hyphen
    \value Key_registered
    \value Key_macron
    \value Key_degree
    \value Key_plusminus
    \value Key_twosuperior
    \value Key_threesuperior
    \value Key_acute
    \value Key_mu
    \value Key_paragraph
    \value Key_periodcentered
    \value Key_cedilla
    \value Key_onesuperior
    \value Key_masculine
    \value Key_guillemotright
    \value Key_onequarter
    \value Key_onehalf
    \value Key_threequarters
    \value Key_questiondown
    \value Key_Agrave
    \value Key_Aacute
    \value Key_Acircumflex
    \value Key_Atilde
    \value Key_Adiaeresis
    \value Key_Aring
    \value Key_AE
    \value Key_Ccedilla
    \value Key_Egrave
    \value Key_Eacute
    \value Key_Ecircumflex
    \value Key_Ediaeresis
    \value Key_Igrave
    \value Key_Iacute
    \value Key_Icircumflex
    \value Key_Idiaeresis
    \value Key_ETH
    \value Key_Ntilde
    \value Key_Ograve
    \value Key_Oacute
    \value Key_Ocircumflex
    \value Key_Otilde
    \value Key_Odiaeresis
    \value Key_multiply
    \value Key_Ooblique
    \value Key_Ugrave
    \value Key_Uacute
    \value Key_Ucircumflex
    \value Key_Udiaeresis
    \value Key_Yacute
    \value Key_THORN
    \value Key_ssharp
    \value Key_division
    \value Key_ydiaeresis
    \value Key_Multi_key
    \value Key_Codeinput
    \value Key_SingleCandidate
    \value Key_MultipleCandidate
    \value Key_PreviousCandidate
    \value Key_Mode_switch
    \value Key_Kanji
    \value Key_Muhenkan
    \value Key_Henkan
    \value Key_Romaji
    \value Key_Hiragana
    \value Key_Katakana
    \value Key_Hiragana_Katakana
    \value Key_Zenkaku
    \value Key_Hankaku
    \value Key_Zenkaku_Hankaku
    \value Key_Touroku
    \value Key_Massyo
    \value Key_Kana_Lock
    \value Key_Kana_Shift
    \value Key_Eisu_Shift
    \value Key_Eisu_toggle
    \value Key_Hangul
    \value Key_Hangul_Start
    \value Key_Hangul_End
    \value Key_Hangul_Hanja
    \value Key_Hangul_Jamo
    \value Key_Hangul_Romaja
    \value Key_Hangul_Jeonja
    \value Key_Hangul_Banja
    \value Key_Hangul_PreHanja
    \value Key_Hangul_PostHanja
    \value Key_Hangul_Special
    \value Key_Dead_Grave
    \value Key_Dead_Acute
    \value Key_Dead_Circumflex
    \value Key_Dead_Tilde
    \value Key_Dead_Macron
    \value Key_Dead_Breve
    \value Key_Dead_Abovedot
    \value Key_Dead_Diaeresis
    \value Key_Dead_Abovering
    \value Key_Dead_Doubleacute
    \value Key_Dead_Caron
    \value Key_Dead_Cedilla
    \value Key_Dead_Ogonek
    \value Key_Dead_Iota
    \value Key_Dead_Voiced_Sound
    \value Key_Dead_Semivoiced_Sound
    \value Key_Dead_Belowdot
    \value Key_Dead_Hook
    \value Key_Dead_Horn
    \value Key_Dead_Stroke
    \value Key_Dead_Abovecomma
    \value Key_Dead_Abovereversedcomma
    \value Key_Dead_Doublegrave
    \value Key_Dead_Belowring
    \value Key_Dead_Belowmacron
    \value Key_Dead_Belowcircumflex
    \value Key_Dead_Belowtilde
    \value Key_Dead_Belowbreve
    \value Key_Dead_Belowdiaeresis
    \value Key_Dead_Invertedbreve
    \value Key_Dead_Belowcomma
    \value Key_Dead_Currency
    \value Key_Dead_a
    \value Key_Dead_A
    \value Key_Dead_e
    \value Key_Dead_E
    \value Key_Dead_i
    \value Key_Dead_I
    \value Key_Dead_o
    \value Key_Dead_O
    \value Key_Dead_u
    \value Key_Dead_U
    \value Key_Dead_Small_Schwa
    \value Key_Dead_Capital_Schwa
    \value Key_Dead_Greek
    \value Key_Dead_Lowline
    \value Key_Dead_Aboveverticalline
    \value Key_Dead_Belowverticalline
    \value Key_Dead_Longsolidusoverlay
    \value Key_Back
    \value Key_Forward
    \value Key_Stop
    \value Key_Refresh
    \value Key_VolumeDown
    \value Key_VolumeMute
    \value Key_VolumeUp
    \value Key_BassBoost
    \value Key_BassUp
    \value Key_BassDown
    \value Key_TrebleUp
    \value Key_TrebleDown
    \value Key_MediaPlay    A key setting the state of the media player to play
    \value Key_MediaStop    A key setting the state of the media player to stop
    \value Key_MediaPrevious
    \value Key_MediaNext
    \value Key_MediaRecord
    \value Key_MediaPause   A key setting the state of the media player to pause (\b Note: not the pause/break key)
    \value Key_MediaTogglePlayPause   A key to toggle the play/pause state in the media player (rather than setting an absolute state)
    \value Key_HomePage
    \value Key_Favorites
    \value Key_Search
    \value Key_Standby
    \value Key_OpenUrl
    \value Key_LaunchMail
    \value Key_LaunchMedia
    \value Key_Launch0 On X11 this key is mapped to "My Computer" (XF86XK_MyComputer) key for legacy reasons.
    \value Key_Launch1 On X11 this key is mapped to "Calculator" (XF86XK_Calculator) key for legacy reasons.
    \value Key_Launch2 On X11 this key is mapped to XF86XK_Launch0 key for legacy reasons.
    \value Key_Launch3 On X11 this key is mapped to XF86XK_Launch1 key for legacy reasons.
    \value Key_Launch4 On X11 this key is mapped to XF86XK_Launch2 key for legacy reasons.
    \value Key_Launch5 On X11 this key is mapped to XF86XK_Launch3 key for legacy reasons.
    \value Key_Launch6 On X11 this key is mapped to XF86XK_Launch4 key for legacy reasons.
    \value Key_Launch7 On X11 this key is mapped to XF86XK_Launch5 key for legacy reasons.
    \value Key_Launch8 On X11 this key is mapped to XF86XK_Launch6 key for legacy reasons.
    \value Key_Launch9 On X11 this key is mapped to XF86XK_Launch7 key for legacy reasons.
    \value Key_LaunchA On X11 this key is mapped to XF86XK_Launch8 key for legacy reasons.
    \value Key_LaunchB On X11 this key is mapped to XF86XK_Launch9 key for legacy reasons.
    \value Key_LaunchC On X11 this key is mapped to XF86XK_LaunchA key for legacy reasons.
    \value Key_LaunchD On X11 this key is mapped to XF86XK_LaunchB key for legacy reasons.
    \value Key_LaunchE On X11 this key is mapped to XF86XK_LaunchC key for legacy reasons.
    \value Key_LaunchF On X11 this key is mapped to XF86XK_LaunchD key for legacy reasons.
    \value Key_LaunchG On X11 this key is mapped to XF86XK_LaunchE key for legacy reasons.
    \value Key_LaunchH On X11 this key is mapped to XF86XK_LaunchF key for legacy reasons.
    \value Key_MonBrightnessUp
    \value Key_MonBrightnessDown
    \value Key_KeyboardLightOnOff
    \value Key_KeyboardBrightnessUp
    \value Key_KeyboardBrightnessDown
    \value Key_PowerOff
    \value Key_WakeUp
    \value Key_Eject
    \value Key_ScreenSaver
    \value Key_WWW
    \value Key_Memo
    \value Key_LightBulb
    \value Key_Shop
    \value Key_History
    \value Key_AddFavorite
    \value Key_HotLinks
    \value Key_BrightnessAdjust
    \value Key_Finance
    \value Key_Community
    \value Key_AudioRewind
    \value Key_BackForward
    \value Key_ApplicationLeft
    \value Key_ApplicationRight
    \value Key_Book
    \value Key_CD
    \value Key_Calculator On X11 this key is not mapped for legacy reasons. Use Qt::Key_Launch1 instead.
    \value Key_ToDoList
    \value Key_ClearGrab
    \value Key_Close
    \value Key_Copy
    \value Key_Cut
    \value Key_Display
    \value Key_DOS
    \value Key_Documents
    \value Key_Excel
    \value Key_Explorer
    \value Key_Game
    \value Key_Go
    \value Key_iTouch
    \value Key_LogOff
    \value Key_Market
    \value Key_Meeting
    \value Key_MenuKB
    \value Key_MenuPB
    \value Key_MySites
    \value Key_News
    \value Key_OfficeHome
    \value Key_Option
    \value Key_Paste
    \value Key_Phone
    \value Key_Calendar
    \value Key_Reply
    \value Key_Reload
    \value Key_RotateWindows
    \value Key_RotationPB
    \value Key_RotationKB
    \value Key_Save
    \value Key_Send
    \value Key_Spell
    \value Key_SplitScreen
    \value Key_Support
    \value Key_TaskPane
    \value Key_Terminal
    \value Key_Tools
    \value Key_Travel
    \value Key_Video
    \value Key_Word
    \value Key_Xfer
    \value Key_ZoomIn
    \value Key_ZoomOut
    \value Key_Away
    \value Key_Messenger
    \value Key_WebCam
    \value Key_MailForward
    \value Key_Pictures
    \value Key_Music
    \value Key_Battery
    \value Key_Bluetooth
    \value Key_WLAN
    \value Key_UWB
    \value Key_AudioForward
    \value Key_AudioRepeat
    \value Key_AudioRandomPlay
    \value Key_Subtitle
    \value Key_AudioCycleTrack
    \value Key_Time
    \value Key_Hibernate
    \value Key_View
    \value Key_TopMenu
    \value Key_PowerDown
    \value Key_Suspend
    \value Key_ContrastAdjust
    \value Key_TouchpadToggle
    \value Key_TouchpadOn
    \value Key_TouchpadOff
    \value Key_MicMute
    \value Key_Red
    \value Key_Green
    \value Key_Yellow
    \value Key_Blue
    \value Key_ChannelUp
    \value Key_ChannelDown
    \value Key_Guide
    \value Key_Info
    \value Key_Settings
    \value Key_MicVolumeUp
    \value Key_MicVolumeDown
    \value Key_New
    \value Key_Open
    \value Key_Find
    \value Key_Undo
    \value Key_Redo
    \value Key_MediaLast
    \value Key_unknown
    \value Key_Call     A key to answer or initiate a call (see Qt::Key_ToggleCallHangup for a key to toggle current call state)
    \value Key_Camera   A key to activate the camera shutter. On Windows Runtime, the environment variable QT_QPA_ENABLE_CAMERA_KEYS must be set to receive the event.
    \value Key_CameraFocus  A key to focus the camera. On Windows Runtime, the environment variable QT_QPA_ENABLE_CAMERA_KEYS must be set to receive the event.
    \value Key_Context1
    \value Key_Context2
    \value Key_Context3
    \value Key_Context4
    \value Key_Flip
    \value Key_Hangup   A key to end an ongoing call (see Qt::Key_ToggleCallHangup for a key to toggle current call state)
    \value Key_No
    \value Key_Select
    \value Key_Yes
    \value Key_ToggleCallHangup A key to toggle the current call state (ie. either answer, or hangup) depending on current call state
    \value Key_VoiceDial
    \value Key_LastNumberRedial
    \value Key_Execute
    \value Key_Printer
    \value Key_Play
    \value Key_Sleep
    \value Key_Zoom
    \value Key_Exit
    \value Key_Cancel
    \sa QKeyEvent::key()
*/
/*!
    \enum Qt::HitTestAccuracy
    This enum contains the types of accuracy that can be used by the
    QTextDocument class when testing for mouse clicks on text documents.
    \value ExactHit The point at which input occurred must coincide
                    exactly with input-sensitive parts of the document.
    \value FuzzyHit The point at which input occurred can lie close to
                    input-sensitive parts of the document.
*/
/*!
    \enum Qt::WhiteSpaceMode
    This enum describes the types of whitespace mode that are used by
    the QTextDocument class to meet the requirements of different kinds
    of textual information.
    \value WhiteSpaceNormal         The whitespace mode used to display
                                    normal word wrapped text in paragraphs.
    \value WhiteSpacePre            A preformatted text mode in which
                                    whitespace is reproduced exactly.
    \value WhiteSpaceNoWrap
    \omitvalue WhiteSpaceModeUndefined
*/
/*!
    \enum Qt::CheckState
    This enum describes the state of checkable items, controls, and widgets.
    \value Unchecked        The item is unchecked.
    \value PartiallyChecked The item is partially checked. Items in hierarchical models
                            may be partially checked if some, but not all, of their
                            children are checked.
    \value Checked          The item is checked.
    \sa QCheckBox, Qt::ItemFlags, Qt::ItemDataRole
*/
/*!
    \enum Qt::ToolButtonStyle
    The style of the tool button, describing how the button's text and
    icon should be displayed.
    \value ToolButtonIconOnly Only display the icon.
    \value ToolButtonTextOnly Only display the text.
    \value ToolButtonTextBesideIcon The text appears beside the icon.
    \value ToolButtonTextUnderIcon The text appears under the icon.
    \value ToolButtonFollowStyle Follow the \l{QStyle::SH_ToolButtonStyle}{style}.
*/
/*!
    \enum Qt::Corner
    This enum type specifies a corner in a rectangle:
    \value TopLeftCorner     The top-left corner of the rectangle.
    \value TopRightCorner    The top-right corner of the rectangle.
    \value BottomLeftCorner  The bottom-left corner of the rectangle.
    \value BottomRightCorner The bottom-right corner of the rectangle.
*/
/*!
    \enum Qt::Edge
    This enum type specifies an edge in a rectangle:
    \value TopEdge    The top edge of the rectangle.
    \value LeftEdge   The left edge of the rectangle.
    \value RightEdge  The right edge of the rectangle.
    \value BottomEdge The bottom edge of the rectangle.
    \since 5.1
*/
/*!
    \enum Qt::ScrollBarPolicy
    This enum type describes the various modes of QAbstractScrollArea's scroll
    bars.
    \value ScrollBarAsNeeded QAbstractScrollArea shows a scroll bar when the
    content is too large to fit and not otherwise. This is the
    default.
    \value ScrollBarAlwaysOff QAbstractScrollArea never shows a scroll bar.
    \value ScrollBarAlwaysOn  QAbstractScrollArea always shows a scroll bar. This
    property is ignored on systems with transient scroll bars (e.g., on Mac from
    version 10.7).
    (The modes for the horizontal and vertical scroll bars are
    independent.)
*/
/*!
    \enum Qt::ArrowType
    \value NoArrow
    \value UpArrow
    \value DownArrow
    \value LeftArrow
    \value RightArrow
*/
/*!
    \enum Qt::FocusReason
    This enum specifies why the focus changed. It will be passed
    through QWidget::setFocus and can be retrieved in the QFocusEvent
    sent to the widget upon focus change.
    \value MouseFocusReason        A mouse action occurred.
    \value TabFocusReason          The Tab key was pressed.
    \value BacktabFocusReason      A Backtab occurred. The input for this may
                                   include the Shift or Control keys;
                                   e.g. Shift+Tab.
    \value ActiveWindowFocusReason The window system made this window either
                                   active or inactive.
    \value PopupFocusReason        The application opened/closed a pop-up that
                                   grabbed/released the keyboard focus.
    \value ShortcutFocusReason     The user typed a label's buddy shortcut
    \value MenuBarFocusReason      The menu bar took focus.
    \value OtherFocusReason        Another reason, usually application-specific.
    \omitvalue NoFocusReason
    \sa {Keyboard Focus in Widgets}
*/
/*!
    \enum Qt::WindowState
    \keyword window state
    This enum type is used to specify the current state of a top-level
    window.
    The states are
    \value WindowNoState   The window has no state set (in normal state).
    \value WindowMinimized The window is minimized (i.e. iconified).
    \value WindowMaximized The window is maximized with a frame around it.
    \value WindowFullScreen The window fills the entire screen without any frame around it.
    \value WindowActive The window is the active window, i.e. it has keyboard focus.
*/
/*!
    \enum Qt::ApplicationState
    \keyword application state
    This enum type is used to specify the current state of the application.
    The states are
    \value ApplicationSuspended    The application is about to suspend. When entering this state, the
                                   application should save its state, cease all activities, and be
                                   prepared for code execution to stop. While suspended, the
                                   application can be killed at any time without further warnings
                                   (e.g. when low memory forces the OS to purge suspended applications).
    \value ApplicationHidden       The application is hidden and runs in the background. This
                                   is the normal state for applications that need to do background
                                   processing, like playing music, while the user interacts with
                                   other applications. The application should free up all graphical
                                   resources when entering this state.
    \value ApplicationInactive     The application is visible, but not selected to be in front.
                                   On desktop platforms, this typically means that the user
                                   activated another application. On mobile platforms, it is
                                   more common to enter this state when the OS is interrupting
                                   the user with e.g. incoming calls or SMS-messages.
                                   While in this state, consider reducing CPU-intensive tasks.
    \value ApplicationActive       The application is visible and selected to be in front.
    \since 5.1
*/
/*!
    \enum Qt::ScreenOrientation
    This enum type specifies the various orientations a screen might have.
    \value PrimaryOrientation           The display's primary orientation.
    \value LandscapeOrientation         Landscape orientation, display width is greater than display height.
    \value PortraitOrientation          Portrait orientation, display height is greater than display width,
                                        rotated 90 degree clockwise relative to landscape.
    \value InvertedLandscapeOrientation Inverted landscape orientation, rotated 180 degrees relative to landscape.
    \value InvertedPortraitOrientation  Inverted portrait orientation, rotated 180 degrees relative to portrait.
*/
/*!
    \enum Qt::ContextMenuPolicy
    This enum type defines the various policies a widget can have with
    respect to showing a context menu.
    \value NoContextMenu the widget does not feature a context menu,
    context menu handling is deferred to the widget's parent.
    \value PreventContextMenu the widget does not feature a context
    menu, and in contrast to \c NoContextMenu, the handling is \e not
    deferred to the widget's parent. This means that all right mouse
    button events are guaranteed to be delivered to the widget itself
    through QWidget::mousePressEvent(), and QWidget::mouseReleaseEvent().
    \value DefaultContextMenu  the widget's QWidget::contextMenuEvent() handler is called.
    \value ActionsContextMenu  the widget displays its QWidget::actions() as context menu.
    \value CustomContextMenu  the widget emits the QWidget::customContextMenuRequested() signal.
*/
/*!
    \enum Qt::FocusPolicy
    This enum type defines the various policies a widget can have with
    respect to acquiring keyboard focus.
    \value TabFocus  the widget accepts focus by tabbing.
    \value ClickFocus  the widget accepts focus by clicking.
    \value StrongFocus  the widget accepts focus by both tabbing
                    and clicking. On \macos this will also
                    be indicate that the widget accepts tab focus
                    when in 'Text/List focus mode'.
    \value WheelFocus  like Qt::StrongFocus plus the widget accepts
                    focus by using the mouse wheel.
    \value NoFocus  the widget does not accept focus.
*/
/*!
    \enum Qt::TabFocusBehavior
    \since 5.5
    This enum type provides different focus behaviors for tab navigation.
    \value NoTabFocus  iterate nothing.
    \value TabFocusTextControls  iterate text controls and widgets.
    \value TabFocusListControls  iterate list controls and widgets.
    \value TabFocusAllControls  iterate all controls and widgets.
*/
/*!
    \enum Qt::ShortcutContext
    For a QEvent::Shortcut event to occur, the shortcut's key sequence
    must be entered by the user in a context where the shortcut is
    active. The possible contexts are these:
    \value WidgetShortcut The shortcut is active when its
    parent widget has focus.
    \value WidgetWithChildrenShortcut The shortcut is active
    when its parent widget, or any of its children has focus.
    Children which are top-level widgets, except pop-ups, are
    not affected by this shortcut context.
    \value WindowShortcut The shortcut is active when its
    parent widget is a logical subwidget of the
    active top-level window.
    \value ApplicationShortcut The shortcut is active when one of
    the applications windows are active.
*/
/*!
    \typedef Qt::WFlags
    \obsolete
    This typedef is obsolete. Use Qt::WindowFlags instead.
    Synonym for Qt::WindowFlags.
*/
/*!
    \enum Qt::WindowType
    \keyword window flag
    This enum type is used to specify various window-system properties
    for the widget. They are fairly unusual but necessary in a few
    cases. Some of these flags depend on whether the underlying window
    manager supports them.
    The main types are
    \value Widget  This is the default type for QWidget. Widgets of
                   this type are child widgets if they have a parent,
                   and independent windows if they have no parent.
                   See also Qt::Window and Qt::SubWindow.
    \value Window  Indicates that the widget is a window, usually
                   with a window system frame and a title bar,
                   irrespective of whether the widget has a parent or
                   not. Note that it is not possible to unset this
                   flag if the widget does not have a parent.
    \value Dialog  Indicates that the widget is a window that should
                   be decorated as a dialog (i.e., typically no
                   maximize or minimize buttons in the title bar).
                   This is the default type for QDialog. If you want
                   to use it as a modal dialog, it should be launched
                   from another window, or have a parent and used
                   with the QWidget::windowModality property. If you make
                   it modal, the dialog will prevent other top-level
                   windows in the application from getting any input.
                   We refer to a top-level window that has a parent
                   as a \e secondary window.
    \value Sheet   Indicates that the window is a sheet on \macos. Since
                   using a sheet implies window modality, the recommended
                   way is to use QWidget::setWindowModality(), or
                   QDialog::open(), instead.
    \value Drawer  Indicates that the widget is a drawer on \macos.
    \value Popup   Indicates that the widget is a pop-up top-level
                   window, i.e. that it is modal, but has a window
                   system frame appropriate for pop-up menus.
    \value Tool    Indicates that the widget is a tool window. A tool
                   window is often a small window with a smaller than
                   usual title bar and decoration, typically used for
                   collections of tool buttons. If there is a parent,
                   the tool window will always be kept on top of it.
                   If there isn't a parent, you may consider using
                   Qt::WindowStaysOnTopHint as well. If the window
                   system supports it, a tool window can be decorated
                   with a somewhat lighter frame. It can also be
                   combined with Qt::FramelessWindowHint.
                   On \macos, tool windows correspond to the
                   \l{https://developer.apple.com/documentation/appkit/nspanel}{NSPanel}
                   class of windows. This means that the window lives on a
                   level above normal windows making it impossible to put a normal
                   window on top of it. By default, tool windows will disappear
                   when the application is inactive.  This can be controlled by
                   the Qt::WA_MacAlwaysShowToolWindow attribute.
    \value ToolTip Indicates that the widget is a tooltip. This is
                   used internally to implement
                   \l{QWidget::toolTip}{tooltips}.
    \value SplashScreen Indicates that the window is a splash screen.
                        This is the default type for QSplashScreen.
    \value Desktop  Indicates that this widget is the desktop. This
                    is the type for QDesktopWidget.
    \value SubWindow  Indicates that this widget is a sub-window, such
                      as a QMdiSubWindow widget.
    \value ForeignWindow Indicates that this window object is a handle
                         representing a native platform window created by
                         another process or by manually using native code.
    \value CoverWindow Indicates that the window represents a cover window,
                       which is shown when the application is minimized on
                       some platforms.
    There are also a number of flags which you can use to customize
    the appearance of top-level windows. These have no effect on other
    windows:
    \value MSWindowsFixedSizeDialogHint  Gives the window a thin dialog border on Windows.
           This style is traditionally used for fixed-size dialogs.
    \value MSWindowsOwnDC  Gives the window its own display
           context on Windows.
    \value BypassWindowManagerHint This flag can be used to indicate to the platform plugin
           that "all" window manager protocols should be disabled. This flag will behave
           different depending on what operating system the application is running on and
           what window manager is running. The flag can be used to get a native window
           with no configuration set.
    \value X11BypassWindowManagerHint  Bypass the window
           manager completely. This results in a borderless window
           that is not managed at all (i.e., no keyboard input unless
           you call QWidget::activateWindow() manually).
    \value FramelessWindowHint  Produces a borderless window.
           The user cannot move or resize a borderless window via the window
           system. On X11, the result of the flag is dependent on the window manager and its
           ability to understand Motif and/or NETWM hints. Most existing
           modern window managers can handle this.
    \value NoDropShadowWindowHint  Disables window drop shadow on supporting platforms.
    The \c CustomizeWindowHint flag is used to enable customization of
    the window controls. This flag must be set to allow the \c
    WindowTitleHint, \c WindowSystemMenuHint, \c
    WindowMinimizeButtonHint, \c WindowMaximizeButtonHint and \c
    WindowCloseButtonHint flags to be changed.
    \value CustomizeWindowHint  Turns off the default window title hints.
    \value WindowTitleHint  Gives the window a title bar.
    \value WindowSystemMenuHint Adds a window system menu, and
    possibly a close button (for example on Mac). If you need to hide
    or show a close button, it is more portable to use \c
    WindowCloseButtonHint.
    \value WindowMinimizeButtonHint  Adds a minimize button. On
           some platforms this implies Qt::WindowSystemMenuHint for it to work.
    \value WindowMaximizeButtonHint  Adds a maximize button. On
           some platforms this implies Qt::WindowSystemMenuHint for it to work.
    \value WindowMinMaxButtonsHint  Adds a minimize and a maximize
           button. On some platforms this implies Qt::WindowSystemMenuHint for it to work.
    \value WindowCloseButtonHint  Adds a close button. On
           some platforms this implies Qt::WindowSystemMenuHint for it
           to work.
    \value WindowContextHelpButtonHint  Adds a context help button to dialogs.
           On some platforms this implies Qt::WindowSystemMenuHint for it to work.
    \value MacWindowToolBarButtonHint On \macos adds a tool bar button (i.e.,
           the oblong button that is on the top right of windows that have toolbars).
    \value WindowFullscreenButtonHint On \macos adds a fullscreen button.
    \value BypassGraphicsProxyWidget Prevents the window and its children from
           automatically embedding themselves into a QGraphicsProxyWidget if the
           parent widget is already embedded. You can set this flag if you
           want your widget to always be a toplevel widget on the desktop,
           regardless of whether the parent widget is embedded in a scene or
           not.
    \value WindowShadeButtonHint Adds a shade button in place of the minimize
           button if the underlying window manager supports it.
    \value WindowStaysOnTopHint  Informs the window system that the
           window should stay on top of all other windows. Note that
           on some window managers on X11 you also have to pass
           Qt::X11BypassWindowManagerHint for this flag to work
           correctly.
    \value WindowStaysOnBottomHint Informs the window system that the
           window should stay on bottom of all other windows.
           \note On X11, this hint will work only in window managers
           that support _NET_WM_STATE_BELOW atom. If a window always
           on the bottom has a parent, the parent will also be left on
           the bottom.  This window hint is currently not implemented
           for \macos.
           \note On Windows, this will work only for frameless or
           full-screen windows.
    \value WindowTransparentForInput Informs the window system that this window
           is used only for output (displaying something) and does not take input.
           Therefore input events should pass through as if it wasn't there.
    \value WindowOverridesSystemGestures Informs the window system that this window
           implements its own set of gestures and that system level gestures, like for
           instance three-finger desktop switching, should be disabled.
    \value WindowDoesNotAcceptFocus Informs the window system that this window should
           not receive the input focus.
    \value MaximizeUsingFullscreenGeometryHint Informs the window system that when
           maximizing the window it should use as much of the available screen geometry
           as possible, including areas that may be covered by system UI such as status
           bars or application launchers. This may result in the window being placed
           under these system UIs, but does not guarantee it, depending on whether or
           not the platform supports it. When the flag is enabled the user is responsible
           for taking QScreen::availableGeometry() into account, so that any UI elements
           in the application that require user interaction are not covered by system UI.
    \value WindowType_Mask  A mask for extracting the window type
                            part of the window flags.
    \sa QWidget::windowFlags, {Window Flags Example}
*/
/*!
    \enum Qt::FindChildOption
    \value FindDirectChildrenOnly    Looks only at the direct children of the object.
    \value FindChildrenRecursively   Looks at all children of the object (recursive search).
*/
/*!
    \enum Qt::DropAction
    \value CopyAction       Copy the data to the target.
    \value MoveAction       Move the data from the source to the target.
    \value LinkAction       Create a link from the source to the target.
    \value ActionMask
    \value IgnoreAction     Ignore the action (do nothing with the data).
    \value TargetMoveAction On Windows, this value is used when the ownership of the D&D data
                            should be taken over by the target application,
                            i.e., the source application should not delete
                            the data.
                            On X11 this value is used to do a move.
                            TargetMoveAction is not used on the Mac.
*/
/*!
    \enum Qt::SortOrder
    This enum describes how the items in a widget are sorted.
    \value AscendingOrder The items are sorted ascending e.g. starts with
    'AAA' ends with 'ZZZ' in Latin-1 locales
    \value DescendingOrder The items are sorted descending e.g. starts with
    'ZZZ' ends with 'AAA' in Latin-1 locales
*/
/*!
    \enum Qt::ClipOperation
    \value NoClip This operation turns clipping off.
    \value ReplaceClip Replaces the current clip path/rect/region with
    the one supplied in the function call.
    \value IntersectClip Intersects the current clip path/rect/region
    with the one supplied in the function call.
*/
/*!
    \enum Qt::ItemSelectionMode
    This enum is used in QGraphicsItem, QGraphicsScene and QGraphicsView to
    specify how items are selected, or how to determine if shapes and items
    collide.
    \value ContainsItemShape The output list contains only items whose
           \l{QGraphicsItem::shape()}{shape} is fully contained inside the
           selection area. Items that intersect with the area's outline are
           not included.
    \value IntersectsItemShape The output list contains both items whose
           \l{QGraphicsItem::shape()}{shape} is fully contained inside the
           selection area, and items that intersect with the area's
           outline. This is a common mode for rubber band selection.
    \value ContainsItemBoundingRect The output list contains only items whose
           \l{QGraphicsItem::boundingRect()}{bounding rectangle} is fully
           contained inside the selection area. Items that intersect with the
           area's outline are not included.
    \value IntersectsItemBoundingRect The output list contains both items
           whose \l{QGraphicsItem::boundingRect()}{bounding rectangle} is
           fully contained inside the selection area, and items that intersect
           with the area's outline. This method is commonly used for
           determining areas that need redrawing.
    \sa QGraphicsScene::items(), QGraphicsScene::collidingItems(),
        QGraphicsView::items(), QGraphicsItem::collidesWithItem(),
        QGraphicsItem::collidesWithPath()
*/
/*!
    \enum Qt::ItemSelectionOperation
    This enum is used in QGraphicsScene to specify what to do with currently selected
    items when setting a selection area.
    \value ReplaceSelection The currently selected items are replaced by items
           in the selection area.
    \value AddToSelection The items in the selection area are added to the currently
           selected items.
    \sa QGraphicsScene::setSelectionArea()
*/
/*!
    \enum Qt::FillRule
    Specifies which method should be used to fill the paths and polygons.
    \value OddEvenFill Specifies that the region is filled using the
    odd even fill rule. With this rule, we determine whether a point
    is inside the shape by using the following method.
    Draw a horizontal line from the point to a location outside the shape,
    and count the number of intersections. If the number of intersections
    is an odd number, the point is inside the shape. This mode is the
    default.
    \value WindingFill Specifies that the region is filled using the
    non zero winding rule. With this rule, we determine whether a
    point is inside the shape by using the following method.
    Draw a horizontal line from the point to a location outside the shape.
    Determine whether the direction of the line at each intersection point
    is up or down. The winding number is determined by summing the
    direction of each intersection. If the number is non zero, the point
    is inside the shape. This fill mode can also in most cases be considered
    as the intersection of closed shapes.
*/
/*!
    \enum Qt::TextFormat
    This enum is used in widgets that can display both plain text and
    rich text, for example QLabel. It is used for deciding whether a text
    string should be interpreted as one or the other. This is normally
    done by passing one of the enum values to a QTextEdit::setTextFormat()
    function.
    \value PlainText  The text string is interpreted as a plain text
        string.
    \value RichText The text string is interpreted as a rich text
        string. See \l {Supported HTML Subset} for the definition
        of rich text.
    \value AutoText The text string is interpreted as for
        Qt::RichText if Qt::mightBeRichText() returns \c true, otherwise
        as Qt::PlainText.
*/
/*!
    \enum Qt::CursorShape
    This enum type defines the various cursors that can be used.
    The standard arrow cursor is the default for widgets in a normal state.
    \value ArrowCursor    \inlineimage cursor-arrow.png
                          The standard arrow cursor.
    \value UpArrowCursor  \inlineimage cursor-uparrow.png
                          An arrow pointing upwards toward the top of the screen.
    \value CrossCursor    \inlineimage cursor-cross.png
                          A crosshair cursor, typically used to help the
                          user accurately select a point on the screen.
    \value WaitCursor     \inlineimage cursor-wait.png
                          An hourglass or watch cursor, usually shown during
                          operations that prevent the user from interacting with
                          the application.
    \value IBeamCursor    \inlineimage cursor-ibeam.png
                          A caret or ibeam cursor, indicating that a widget can
                          accept and display text input.
    \value SizeVerCursor  \inlineimage cursor-sizev.png
                          A cursor used for elements that are used to vertically
                          resize top-level windows.
    \value SizeHorCursor  \inlineimage cursor-sizeh.png
                          A cursor used for elements that are used to horizontally
                          resize top-level windows.
    \value SizeBDiagCursor  \inlineimage cursor-sizeb.png
                          A cursor used for elements that are used to diagonally
                          resize top-level windows at their top-right and
                          bottom-left corners.
    \value SizeFDiagCursor  \inlineimage cursor-sizef.png
                          A cursor used for elements that are used to diagonally
                          resize top-level windows at their top-left and
                          bottom-right corners.
    \value SizeAllCursor  \inlineimage cursor-sizeall.png
                          A cursor used for elements that are used to resize
                          top-level windows in any direction.
    \value BlankCursor    A blank/invisible cursor, typically used when the cursor
                          shape needs to be hidden.
    \value SplitVCursor   \inlineimage cursor-vsplit.png
                          A cursor used for vertical splitters, indicating that
                          a handle can be dragged horizontally to adjust the use
                          of available space.
    \value SplitHCursor   \inlineimage cursor-hsplit.png
                          A cursor used for horizontal splitters, indicating that
                          a handle can be dragged vertically to adjust the use
                          of available space.
    \value PointingHandCursor  \inlineimage cursor-hand.png
                          A pointing hand cursor that is typically used for
                          clickable elements such as hyperlinks.
    \value ForbiddenCursor  \inlineimage cursor-forbidden.png
                          A slashed circle cursor, typically used during drag
                          and drop operations to indicate that dragged content
                          cannot be dropped on particular widgets or inside
                          certain regions.
    \value OpenHandCursor \inlineimage cursor-openhand.png
                          A cursor representing an open hand, typically used to
                          indicate that the area under the cursor is the visible
                          part of a canvas that the user can click and drag in
                          order to scroll around.
    \value ClosedHandCursor \inlineimage cursor-closedhand.png
                          A cursor representing a closed hand, typically used to
                          indicate that a dragging operation is in progress that
                          involves scrolling.
    \value WhatsThisCursor  \inlineimage cursor-whatsthis.png
                          An arrow with a question mark, typically used to indicate
                          the presence of What's This? help for a widget.
    \value BusyCursor     \inlineimage cursor-busy.png
                          An hourglass or watch cursor, usually shown during
                          operations that allow the user to interact with
                          the application while they are performed in the
                          background.
    \value DragMoveCursor
                          A cursor that is usually used when dragging an item.
    \value DragCopyCursor
                          A cursor that is usually used when dragging an item
                          to copy it.
    \value DragLinkCursor
                          A cursor that is usually used when dragging an item
                          to make a link to it.
    \value BitmapCursor
    \omitvalue LastCursor
    \omitvalue CustomCursor
*/
/*!
    \enum Qt::LayoutDirection
    Specifies the direction of Qt's layouts and text handling.
    \value LeftToRight  Left-to-right layout.
    \value RightToLeft  Right-to-left layout.
    \value LayoutDirectionAuto   Automatic layout.
    Right-to-left layouts are necessary for certain languages,
    notably Arabic and Hebrew.
    LayoutDirectionAuto serves two purposes. When used in conjunction with widgets and layouts, it
    will imply to use the layout direction set on the parent widget or QApplication. This
    has the same effect as QWidget::unsetLayoutDirection().
    When LayoutDirectionAuto is used in conjunction with text layouting, it will imply that the text
    directionality is determined from the content of the string to be layouted.
    \sa QGuiApplication::setLayoutDirection(), QWidget::setLayoutDirection(), QTextOption::setTextDirection(), QString::isRightToLeft()
*/
/*!
    \enum Qt::AnchorPoint
    Specifies a side of a layout item that can be anchored. This is used by
    QGraphicsAnchorLayout.
    \value AnchorLeft               The left side of a layout item.
    \value AnchorHorizontalCenter   A "virtual" side that is centered between the left and the
                                    right side of a layout item.
    \value AnchorRight              The right side of a layout item.
    \value AnchorTop                The top side of a layout item.
    \value AnchorVerticalCenter     A "virtual" side that is centered between the top and the
                                    bottom side of a layout item.
    \value AnchorBottom             The bottom side of a layout item.
    \sa QGraphicsAnchorLayout
*/
/*!
    \enum Qt::InputMethodHint
    \value ImhNone                   No hints.
    Flags that alter the behavior:
    \value ImhHiddenText             The input method should not show the characters while typing.
                                     This is automatically set when setting QLineEdit::echoMode to \c Password.
                                     Note that setting \c ImhHiddenText does not change the echo mode.
    \value ImhSensitiveData          Typed text should not be stored by the active input method
                                     in any persistent storage like predictive user dictionary.
    \value ImhNoAutoUppercase        The input method should not try to automatically switch to upper case
                                     when a sentence ends.
    \value ImhPreferNumbers          Numbers are preferred (but not required).
    \value ImhPreferUppercase        Upper case letters are preferred (but not required).
    \value ImhPreferLowercase        Lower case letters are preferred (but not required).
    \value ImhNoPredictiveText       Do not use predictive text (i.e. dictionary lookup) while typing.
    \value ImhDate                   The text editor functions as a date field.
    \value ImhTime                   The text editor functions as a time field.
    \value ImhPreferLatin            Latin characters are preferred (but not required).
    \value ImhMultiLine              Multiple lines can be entered into the text field.
    \value ImhNoEditMenu             Do not use built-in edit menu. This flag was introduced in Qt 5.11.
    \value ImhNoTextHandles          Do not use built-in text cursor and selection handles. This flag was introduced in Qt 5.11.
    Flags that restrict input (exclusive flags):
    \value ImhDigitsOnly             Only digits are allowed.
    \value ImhFormattedNumbersOnly   Only number input is allowed. This includes decimal point and minus sign.
    \value ImhUppercaseOnly          Only upper case letter input is allowed.
    \value ImhLowercaseOnly          Only lower case letter input is allowed.
    \value ImhDialableCharactersOnly Only characters suitable for phone dialing are allowed.
    \value ImhEmailCharactersOnly    Only characters suitable for email addresses are allowed.
    \value ImhUrlCharactersOnly      Only characters suitable for URLs are allowed.
    \value ImhLatinOnly              Only latin based input is allowed.
    Masks:
    \value ImhExclusiveInputMask     This mask yields nonzero if any of the exclusive flags are used.
    \note If several exclusive flags are OR-ed together, the resulting character set will
          consist of the union of the specified sets. For instance specifying \c ImhNumbersOnly and
          \c ImhUppercaseOnly would yield a set consisting of numbers and uppercase letters.
    \sa QGraphicsItem::inputMethodHints()
*/
/*!
    \enum Qt::InputMethodQuery
    \value ImEnabled            The widget accepts input method input.
    \value ImMicroFocus         This query is obsolete. Use \c ImCursorRectangle instead.
    \value ImCursorRectangle    The rectangle covering the area of the input cursor in widget coordinates.
    \value ImFont               The currently used font for text input.
    \value ImCursorPosition     The logical position of the cursor within the text surrounding the input area
                                (see \c ImSurroundingText).
    \value ImSurroundingText    The plain text around the input area, for example the current paragraph.
    \value ImCurrentSelection   The currently selected text.
    \value ImMaximumTextLength  The maximum number of characters that the widget can hold. If there is no limit,
                                QVariant::QVariant() is returned.
    \value ImAnchorPosition     The position of the selection anchor. This may be less or greater than
                                \c ImCursorPosition, depending on which side of selection the cursor is.
                                If there is no selection, it returns the same as \c ImCursorPosition.
    \value ImHints              The hints for input method on expected input. (See Qt::InputMethodHints)
    \value ImPreferredLanguage  The preferred input language.
    \value ImPlatformData       Platform specific data for input method.
    \value ImAbsolutePosition   The logical position of the cursor within the entire document.
    \value ImTextBeforeCursor   The plain text before the cursor. The widget can decide how much text to return,
                                but \b{must} not return an empty string unless the cursor is at the start of the document.
    \value ImTextAfterCursor    The plain text after the cursor. The widget can decide how much text to return,
                                but \b{must} not return an empty string unless the cursor is at the end of the document.
    \value ImEnterKeyType       The Enter key type.
    \value ImAnchorRectangle    The bounding rectangle of the selection anchor.
                                This value was added in Qt 5.7.
    \value ImInputItemClipRectangle The actual exposed input item rectangle. Parts of the input item might be
                                clipped. This value will take clipping into consideration and return the actual painted
                                item rectangle. The rectangle is in widget coordinates.
    Masks:
    \value ImQueryInput         Commonly changed properties on input.
    \value ImQueryAll           Query for all input method properties.
    \sa QInputMethodQueryEvent
*/
/*!
    \enum Qt::EnterKeyType
    This can be used to alter the appearance of the Return key on an on-screen keyboard.
    \note Not all of these values are supported on all platforms.
    For unsupported values the default key will be used instead.
    \value EnterKeyDefault     The default Enter key.
                               This can either be a button closing the keyboard, or a Return button
                               causing a new line in case of a multi-line input field.
    \value EnterKeyReturn      Show a Return button that inserts a new line.
                               The keyboard will not close when this button is pressed.
    \value EnterKeyDone        Show a "Done" button.
                               The keyboard will close when this button is pressed.
    \value EnterKeyGo          Show a "Go" button.
                               Typically used in an address bar when entering a URL; the keyboard
                               will close when this button is pressed.
    \value EnterKeySend        Show a "Send" button.
                               The keyboard will close when this button is pressed.
    \value EnterKeySearch      Show a "Search" button.
                               The keyboard will close when this button is pressed.
    \value EnterKeyNext        Show a "Next" button.
                               Typically used in a form to allow navigating to the next input field;
                               the keyboard will not close when this button is pressed.
    \value EnterKeyPrevious    Show a "Previous" button.
                               The keyboard will not close when this button is pressed.
    \since 5.6
*/
/*!
    \enum Qt::ItemDataRole
    Each item in the model has a set of data elements associated with
    it, each with its own role. The roles are used by the view to indicate
    to the model which type of data it needs. Custom models should return
    data in these types.
    The general purpose roles (and the associated types) are:
    \value DisplayRole    The key data to be rendered in the form of text. (QString)
    \value DecorationRole The data to be rendered as a decoration in the form
                          of an icon. (QColor, QIcon or QPixmap)
    \value EditRole       The data in a form suitable for editing in an
                          editor. (QString)
    \value ToolTipRole    The data displayed in the item's tooltip. (QString)
    \value StatusTipRole  The data displayed in the status bar. (QString)
    \value WhatsThisRole  The data displayed for the item in "What's This?"
                          mode. (QString)
    \value SizeHintRole   The size hint for the item that will be supplied
                          to views. (QSize)
    Roles describing appearance and meta data (with associated types):
    \value FontRole             The font used for items rendered with the default
                                delegate. (QFont)
    \value TextAlignmentRole    The alignment of the text for items rendered with the
                                default delegate. (Qt::Alignment)
    \value BackgroundRole       The background brush used for items rendered with
                                the default delegate. (QBrush)
    \value BackgroundColorRole  This role is obsolete. Use BackgroundRole instead.
    \value ForegroundRole       The foreground brush (text color, typically)
                                used for items rendered with the default delegate.
                                (QBrush)
    \value TextColorRole        This role is obsolete. Use ForegroundRole instead.
    \value CheckStateRole       This role is used to obtain the checked state of
                                an item. (Qt::CheckState)
    \value InitialSortOrderRole This role is used to obtain the initial sort order
                                of a header view section. (Qt::SortOrder). This
                                role was introduced in Qt 4.8.
    Accessibility roles (with associated types):
    \value AccessibleTextRole        The text to be used by accessibility
                                     extensions and plugins, such as screen
                                     readers. (QString)
    \value AccessibleDescriptionRole A description of the item for accessibility
                                     purposes. (QString)
    User roles:
    \value UserRole       The first role that can be used for application-specific purposes.
    \omitvalue DisplayPropertyRole
    \omitvalue DecorationPropertyRole
    \omitvalue ToolTipPropertyRole
    \omitvalue StatusTipPropertyRole
    \omitvalue WhatsThisPropertyRole
    For user roles, it is up to the developer to decide which types to use and ensure that
    components use the correct types when accessing and setting data.
*/
/*!
    \enum Qt::ItemFlag
    This enum describes the properties of an item:
    \value NoItemFlags It does not have any properties set.
    \value ItemIsSelectable It can be selected.
    \value ItemIsEditable It can be edited.
    \value ItemIsDragEnabled It can be dragged.
    \value ItemIsDropEnabled It can be used as a drop target.
    \value ItemIsUserCheckable It can be checked or unchecked by the user.
    \value ItemIsEnabled The user can interact with the item.
    \value ItemIsAutoTristate The item's state depends on the state of its children.
           This enables automatic management of the state of parent items in QTreeWidget
           (checked if all children are checked, unchecked if all children are unchecked,
           or partially checked if only some children are checked).
    \value ItemIsTristate \e{This enum value is deprecated.} Use Qt::ItemIsAutoTristate
    instead.
    \value ItemNeverHasChildren The item never has child items.
           This is used for optimization purposes only.
    \value ItemIsUserTristate The user can cycle through three separate states.
           This value was added in Qt 5.5.
    Note that checkable items need to be given both a suitable set of flags
    and an initial state, indicating whether the item is checked or not.
    This is handled automatically for model/view components, but needs
    to be explicitly set for instances of QListWidgetItem, QTableWidgetItem,
    and QTreeWidgetItem.
    Note that it is undefined behavior to reimplement QAbstractItemModel::hasChildren
    to return true for an index if that index has the Qt::ItemNeverHasChildren flag set.
    \sa QAbstractItemModel
*/
/*!
    \enum Qt::MatchFlag
    This enum describes the type of matches that can be used when searching
    for items in a model.
    \value MatchExactly     Performs QVariant-based matching.
    \value MatchFixedString Performs string-based matching.
           String-based comparisons are case-insensitive unless the
           \c MatchCaseSensitive flag is also specified.
    \value MatchContains    The search term is contained in the item.
    \value MatchStartsWith  The search term matches the start of the item.
    \value MatchEndsWith    The search term matches the end of the item.
    \value MatchCaseSensitive  The search is case sensitive.
    \value MatchRegExp      Performs string-based matching using a regular
           expression as the search term.
    \value MatchWildcard    Performs string-based matching using a string with
           wildcards as the search term.
    \value MatchWrap        Perform a search that wraps around, so that when
           the search reaches the last item in the model, it begins again at
           the first item and continues until all items have been examined.
    \value MatchRecursive   Searches the entire hierarchy.
    \sa QString::compare(), QRegExp
*/
/*!
    \enum Qt::TextElideMode
    This enum specifies where the ellipsis should appear when
    displaying texts that don't fit:
    \value ElideLeft    The ellipsis should appear at the beginning of the text.
    \value ElideRight   The ellipsis should appear at the end of the text.
    \value ElideMiddle  The ellipsis should appear in the middle of the text.
    \value ElideNone    Ellipsis should NOT appear in the text.
    Qt::ElideMiddle is normally the most appropriate choice for URLs (e.g.,
    "\l{http://bugreports.qt.io/browse/QTWEBSITE-13}{http://bugreports.qt.../QTWEBSITE-13/}"),
    whereas Qt::ElideRight is appropriate
    for other strings (e.g.,
    "\l{http://doc.qt.io/archives/qq/qq09-mac-deployment.html}{Deploying Applications on Ma...}").
    \sa QAbstractItemView::textElideMode, QFontMetrics::elidedText(), AlignmentFlag, QTabBar::elideMode
*/
/*!
    \enum Qt::WindowModality
    \keyword modal
    This enum specifies the behavior of a modal window. A modal window
    is one that blocks input to other windows. Note that windows that
    are children of a modal window are not blocked.
    The values are:
    \value NonModal         The window is not modal and does not block input to other windows.
    \value WindowModal      The window is modal to a single window hierarchy and blocks input to its parent window, all grandparent windows, and all siblings of its parent and grandparent windows.
    \value ApplicationModal The window is modal to the application and blocks input to all windows.
    \sa QWidget::windowModality, QDialog
*/
/*!
    \enum Qt::TextInteractionFlag
    This enum specifies how a text displaying widget reacts to user input.
    \value NoTextInteraction          No interaction with the text is possible.
    \value TextSelectableByMouse      Text can be selected with the mouse and copied to the clipboard using
                                      a context menu or standard keyboard shortcuts.
    \value TextSelectableByKeyboard   Text can be selected with the cursor keys on the keyboard. A text cursor is shown.
    \value LinksAccessibleByMouse     Links can be highlighted and activated with the mouse.
    \value LinksAccessibleByKeyboard  Links can be focused using tab and activated with enter.
    \value TextEditable               The text is fully editable.
    \value TextEditorInteraction      The default for a text editor.
    \value TextBrowserInteraction     The default for QTextBrowser.
*/
/*!
    \enum Qt::MaskMode
    This enum specifies the behavior of the
    QPixmap::createMaskFromColor() and QImage::createMaskFromColor()
    functions.
    \value MaskInColor   Creates a mask where all pixels matching the given color are opaque.
    \value MaskOutColor  Creates a mask where all pixels matching the given color are transparent.
*/
/*!
    \enum Qt::DockWidgetAreaSizes
    \internal
*/
/*!
    \enum Qt::ToolBarAreaSizes
    \internal
*/
/*!
    \enum Qt::EventPriority
    This enum can be used to specify event priorities.
    \value HighEventPriority Events with this priority are sent before
    events with NormalEventPriority or LowEventPriority.
    \value NormalEventPriority Events with this priority are sent
    after events with HighEventPriority, but before events with
    LowEventPriority.
    \value LowEventPriority Events with this priority are sent after
    events with HighEventPriority or NormalEventPriority.
    Note that these values are provided purely for convenience, since
    event priorities can be any value between \c INT_MAX and \c
    INT_MIN, inclusive. For example, you can define custom priorities
    as being relative to each other:
    \snippet code/doc_src_qnamespace.cpp 1
    \sa QCoreApplication::postEvent()
*/
/*!
    \enum Qt::SizeHint
    \since 4.4
    This enum is used by QGraphicsLayoutItem::sizeHint()
    \value MinimumSize is used to specify the minimum size of a graphics layout item.
    \value PreferredSize is used to specify the preferred size of a graphics layout item.
    \value MaximumSize is used to specify the maximum size of a graphics layout item.
    \value MinimumDescent is used to specify the minimum descent of a text string in a graphics layout item.
    \omitvalue NSizeHints
    \sa QGraphicsLayoutItem::sizeHint()
*/
/*!
    \enum Qt::SizeMode
    \since 4.4
    This enum is used by QPainter::drawRoundedRect() and QPainterPath::addRoundedRect()
    functions to specify the radii of rectangle corners with respect to the dimensions
    of the bounding rectangles specified.
    \value AbsoluteSize Specifies the size using absolute measurements.
    \value RelativeSize Specifies the size relative to the bounding rectangle,
                        typically using percentage measurements.
*/
/*!
    \enum Qt::WindowFrameSection
    \since 4.4
    This enum is used to describe parts of a window frame. It is returned by
    QGraphicsWidget::windowFrameSectionAt() to describe what section of the window
    frame is under the mouse.
    \value NoSection
    \value LeftSection
    \value TopLeftSection
    \value TopSection
    \value TopRightSection
    \value RightSection
    \value BottomRightSection
    \value BottomSection
    \value BottomLeftSection
    \value TitleBarArea
    \sa QGraphicsWidget::windowFrameEvent()
    \sa QGraphicsWidget::paintWindowFrame()
    \sa QGraphicsWidget::windowFrameSectionAt()
*/
/*!
  \enum Qt::TileRule
  \since 4.6
  This enum describes how to repeat or stretch the parts of an image
  when drawing.
  \value StretchTile  Scale the image to fit to the available area.
  \value RepeatTile   Repeat the image until there is no more space. May
  crop the last image.
  \value RoundTile    Similar to Repeat, but scales the image down to
  ensure that the last tile is not cropped.
*/
/*!
    \enum Qt::Initialization
    \internal
*/
/*!
    \enum Qt::CoordinateSystem
    \since 4.6
    This enum specifies the coordinate system.
    \value DeviceCoordinates Coordinates are relative to the top-left corner
    of the object's paint device.
    \value LogicalCoordinates Coordinates are relative to the top-left corner
    of the object.
*/
/*! \enum Qt::TouchPointState
    \since 4.6
    This enum represents the state of a touch point at the time a
    QTouchEvent occurred.
    \value TouchPointPressed The touch point is now pressed.
    \value TouchPointMoved The touch point moved.
    \value TouchPointStationary The touch point did not move.
    \value TouchPointReleased The touch point was released.
*/
/*!
    \enum Qt::GestureState
    \since 4.6
    This enum type describes the state of a gesture.
    \value NoGesture        No gesture has been detected.
    \value GestureStarted   A continuous gesture has started.
    \value GestureUpdated   A gesture continues.
    \value GestureFinished  A gesture has finished.
    \value GestureCanceled  A gesture was canceled.
    \sa QGesture
*/
/*!
    \enum Qt::GestureType
    \since 4.6
    This enum type describes the standard gestures.
    \value TapGesture        A Tap gesture.
    \value TapAndHoldGesture A Tap-And-Hold (Long-Tap) gesture.
    \value PanGesture        A Pan gesture.
    \value PinchGesture      A Pinch gesture.
    \value SwipeGesture      A Swipe gesture.
    \value CustomGesture A flag that can be used to test if the gesture is a
    user-defined gesture ID.
    \omitvalue LastGestureType
    User-defined gestures are registered with the
    QGestureRecognizer::registerRecognizer() function which generates a custom
    gesture ID with the Qt::CustomGesture flag set.
    \sa QGesture, QWidget::grabGesture(), QGraphicsObject::grabGesture()
*/
/*!
    \enum Qt::GestureFlag
    \since 4.6
    This enum type describes additional flags that can be used when subscribing
    to a gesture.
    \value DontStartGestureOnChildren By default gestures can start on the
    widget or over any of its children. Use this flag to disable this and allow
    a gesture to start on the widget only.
    \value ReceivePartialGestures Allows any ignored gesture events to be
    propagated to parent widgets which have specified this hint. By default
    only gestures that are in the Qt::GestureStarted state are propagated and
    the widget always gets the full gesture sequence starting with a gesture in
    the Qt::GestureStarted state and ending with a gesture in the
    Qt::GestureFinished or Qt::GestureCanceled states.
    \value IgnoredGesturesPropagateToParent Since Qt 4.7, this flag allows you
    to fine-tune gesture event propagation. By setting the flag when
    \l{QGraphicsObject::grabGesture()}{grabbing} a gesture all ignored partial
    gestures will propagate to their parent items.
    \sa QWidget::grabGesture(), QGraphicsObject::grabGesture()
*/
/*!
    \enum Qt::NativeGestureType
    \since 5.2
    This enum returns the gesture type.
    \value BeginNativeGesture Sent before gesture event stream.
    \value EndNativeGesture   Sent after gesture event stream.
    \value PanNativeGesture   Sent after a panning gesture.
                              Similar to a click-and-drag mouse movement.
    \value ZoomNativeGesture  Specifies the magnification delta in percent.
    \value SmartZoomNativeGesture Boolean magnification state.
    \value RotateNativeGesture    Rotation delta in degrees.
    \value SwipeNativeGesture     Sent after a swipe movements.
*/
/*!
    \enum Qt::NavigationMode
    \since 4.6
    This enum type describes the mode for moving focus.
    \value NavigationModeNone                Only the touch screen is used.
    \value NavigationModeKeypadTabOrder      Qt::Key_Up and Qt::Key_Down are used to change focus.
    \value NavigationModeKeypadDirectional   Qt::Key_Up, Qt::Key_Down, Qt::Key_Left and Qt::Key_Right are used to change focus.
    \value NavigationModeCursorAuto          The mouse cursor is used to change focus,
                                             it is displayed only on non touchscreen devices.
                                             The keypad is used to implement a virtual cursor, unless
                                             the device has an analog mouse type of input device (e.g. touchpad).
                                             This is the recommended setting for an application such as a web browser that
                                             needs pointer control on both touch and non-touch devices.
    \value NavigationModeCursorForceVisible  The mouse cursor is used to change focus,
                                             it is displayed regardless of device type.
                                             The keypad is used to implement a virtual cursor, unless
                                             the device has an analog mouse type of input device (e.g. touchpad)
    \note Cursor navigation is not currently implemented on any platform
    and behaves as NavigationModeNone.
    \sa QApplication::setNavigationMode()
    \sa QApplication::navigationMode()
*/
/*!
    \enum Qt::CursorMoveStyle
    This enum describes the movement style available to text cursors. The options
    are:
    \value LogicalMoveStyle Within a left-to-right text block, decrease cursor
    position when pressing left arrow key, increase cursor position when pressing
    the right arrow key. If the text block is right-to-left, the opposite behavior
    applies.
    \value VisualMoveStyle Pressing the left arrow key will always cause the cursor
    to move left, regardless of the text's writing direction. Pressing the right
    arrow key will always cause the cursor to move right.
*/
/*!
    \enum Qt::TimerType
    The timer type indicates how accurate a timer can be.
    \value PreciseTimer Precise timers try to keep millisecond accuracy
    \value CoarseTimer Coarse timers try to keep accuracy within 5% of the desired interval
    \value VeryCoarseTimer Very coarse timers only keep full second accuracy
    On UNIX (including Linux, \macos, and iOS), Qt will keep millisecond accuracy
    for Qt::PreciseTimer. For Qt::CoarseTimer, the interval will be adjusted up
    to 5% to align the timer with other timers that are expected to fire at or
    around the same time. The objective is to make most timers wake up at the
    same time, thereby reducing CPU wakeups and power consumption.
    On Windows, Qt will use Windows's Multimedia timer facility (if available)
    for Qt::PreciseTimer and normal Windows timers for Qt::CoarseTimer and
    Qt::VeryCoarseTimer.
    On all platforms, the interval for Qt::VeryCoarseTimer is rounded to the
    nearest full second (e.g. an interval of 23500ms will be rounded to
    24000ms, and 20300ms to 20000ms).
*/
/*!
    \enum Qt::ScrollPhase
    \since 5.2
    This enum describes the phase of scrolling.
    \value NoScrollPhase The input device doesn't support scroll phase.
    This value was introduced in Qt 5.7.
    \value ScrollBegin Scrolling is about to begin, but the scrolling
    distance did not yet change.
    \value ScrollUpdate The scrolling distance has changed (default).
    \value ScrollEnd Scrolling has ended, but the scrolling distance
    did not change anymore.
*/
/*!
    \enum Qt::MouseEventSource
    \since 5.3
    This enum describes the source of a mouse event and can be useful
    to determine if the event is an artificial mouse event originating
    from another device such as a touchscreen.
    \value MouseEventNotSynthesized The most common value. On
    platforms where such information is available this value indicates
    that the event was generated in response to a genuine mouse event
    in the system.
    \value MouseEventSynthesizedBySystem Indicates that the mouse
    event was synthesized from a touch event by the platform.
    \value MouseEventSynthesizedByQt Indicates that the mouse event was
    synthesized from an unhandled touch event by Qt.
    \value MouseEventSynthesizedByApplication Indicates that the mouse
    event was synthesized by the application. This allows
    distinguishing application-generated mouse events from the ones
    that are coming from the system or are synthesized by Qt. This
    value was introduced in Qt 5.6
    \sa Qt::AA_SynthesizeMouseForUnhandledTouchEvents
*/
/*!
    \enum Qt::MouseEventFlag
    \since 5.3
    This enum provides additional information concerning a QMouseEvent.
    \value MouseEventCreatedDoubleClick Indicates that Qt has created a
    \l {QEvent::MouseButtonDblClick}{MouseButtonDblClick} event from this event. The flag is set in the causing
    \l {QEvent::MouseButtonPress}{MouseButtonPress}, and not in the resulting \l {QEvent::MouseButtonDblClick}{MouseButtonDblClick}.
    \omitvalue MouseEventFlagMask
*/
/*!
  \enum Qt::ChecksumType
  \since 5.9
  This enum describes the possible standards used by qChecksum().
  \value ChecksumIso3309 Checksum calculation based on ISO 3309.
  \value ChecksumItuV41 Checksum calculation based on ITU-V.41.
*/

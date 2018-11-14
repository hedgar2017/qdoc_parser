 /*!
    \a Class
    \b {a very bold text \\b}

    \inmodule MegaModule

    \badcode
        int main(int argc, char *argv[])
        {
            ...
        }
    \endcode

    \brief The brief explanation
           of everything
    \c Codeword

    \c {Bracketed codeword}

    \e {Bracketed eeeeeeee}

    \class Class

    \code
    These are
    multiline code
    \endcode

    \codeline This is codeline
    
    \div
        int main(int argc, char *argv[])
        {
            ...
        }
    \enddiv

    \dots \e {a very italic text \\e}

    \gui{GUI}

    \image image.jpg "Just an image"
    \inlineimage image.jpg Just an inline image

    \legalese
    These are
    licence lines
    \endlegalese

    \macos
    \note A Mega
    Ultra multiline note
    with some useless text

    \newcode
        int main(int argc, char *argv[])
        {
            ...
        }
    \endcode

    \deprecated Deprecated stuff
    \obsolete Obsolete stuff
    \page Page stuff
    \quotefile Quotefile stuff
    \reentrant Reentrant stuff
    \relates Relates stuff
    \row Row stuff
    \preliminary Preliminary stuff
    \reimp Reimp stuff
    \since Since stuff
    \snippet Snippet stuff

    \table
        \header A header
        \headerfile <QHeaderFile>

        Table stuff
    \endtable

    \tableofcontents Tableofcontents stuff
    \target Target stuff
    \threadsafe Threadsafe stuff
    \typedef Typedef stuff

    \property Property

    \overload void overloadedFunction() const volatile override

    \uicontrol UIcontrol

    \variable Variable

    \warning A Mega
    Ultra multiline warning
    with some useless text

    \sa removeAction(), QMenu,
        addAction(), QWidget,
    testFunction()

    \section1 Basic Qt
    This is the first section.
    \section2 Getting Started
    This is the second subsection.
    \section3 Hello Qt
    This is the third subsubsection.
    \section4 Bye Qt
    This is the fourth subsubsection.

    \list
    \li Basic Qt
    \li Getting Started
    \li \e Hello Qt
    \li \c Bye Qt
    \li
    \endlist

    \l [PAGE] {http://google.com} {Google}
    \l {assertions} {assertions}
    \l QWidget
    \l QWidget::sizeHint()
    \l <QtGlobal>
    \l widgets/wiggly
    \l {QWidget Class Reference}
    \l {Introduction to QDoc}
    \l fontmatching
    \l {Shared Classes}
    \l http://qt-project.org/

    \unicode DEAD

    Some text with a quoted command "\class"
    Some text with a quoted command "\\class"
    Some text with a quoted\\quoted command "c:\windows\data"

    \title Title
    \namespace Namespace

    \keyword some keyword

    \param param1 some param stuff
    \param param2 another param stuff
    
    QWidgetBackingStoreTracker is a thin wrapper around a \a QWidgetBackingStore pointer,
    which maintains a list of the \b {QWidgets} which are currently using the backing
    store.  This list is modified via the \underline{registerWidget} and unregisterWidget functions.

    \fn void function() const volatile
 */
 // a single line comment
   /* a
   multiline
     one */
function1() {}

/*!
    \enum TheEnum

    \value TopLeftCorner
           The top-left corner of the rectangle.
           
    \value TopRightCorner
           The top-right corner of the rectangle.
           
    \value RearCorner Rear corner of the rectangle.
           
    \value FrontCorner Front corner of the rectangle.

    \value BottomLeftCorner
    
    \value BottomRightCorner
*/
function2() {}

/*!
    \l {https://github.com/emoon/qdoc_parser/issues/1} {Issue 1}

    \enum QWidget::RenderFlag

    This enum describes how to render the widget when calling QWidget::render().

    \value DrawWindowBackground If you enable this option, the widget's background
    is rendered into the target even if autoFillBackground is not set. By default,
    this option is enabled.

    \value DrawChildren If you enable this option, the widget's children
    are rendered recursively into the target. By default, this option is enabled.

    \value IgnoreMask If you enable this option, the widget's QWidget::mask()
    is ignored when rendering into the target. By default, this option is disabled.

    \since 4.3
*/
function3() {}

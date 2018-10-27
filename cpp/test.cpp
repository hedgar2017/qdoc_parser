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

    \fn void function() const volatile

    \gui{GUI}

    \image image.jpg "Just an image"
    \inlineimage image.jpg Just an inline image

    \l [PAGE] {http://google.com} {Google}
    \l {assertions} {assertions}

    \legalese
    These are
    licence lines
    \endlegalese

    \macos \note Note

    \newcode
        int main(int argc, char *argv[])
        {
            ...
        }
    \endcode

    \deprecated Deprecated stuff
    \internal Internal stuff
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

    \warning Warning, intruder!

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

    \li Basic Qt
    \li Getting Started
    \li Hello Qt
    \li Bye Qt
    
    QWidgetBackingStoreTracker is a thin wrapper around a \a QWidgetBackingStore pointer,
    which maintains a list of the \b {QWidgets} which are currently using the backing
    store.  This list is modified via the \underline{registerWidget} and unregisterWidget functions.
 */
 // a single line comment
   /* a
   multiline
     one */
QWidgetBackingStoreTracker::QWidgetBackingStoreTracker() {}

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
enum TheEnum {}

import sys
import glob

header = r'''
\documentclass[10.5pt]{article}
\usepackage[top=20truemm,bottom=20truemm,left=20truemm,right=20truemm]{geometry}

% User defined
\usepackage{xeCJK}
\usepackage{fontspec}
\setmonofont{DejaVu Sans Mono}
\usepackage{color}
\usepackage{listings}
\lstset{
 columns=fixed,
 numbers=left,
 numberstyle=\tiny,
 frame=none,
 % backgroundcolor=\color[RGB]{245,245,244},
 keywordstyle=\color[RGB]{40,40,255},
 basicstyle=\ttfamily,
 % numberstyle=\footnotesize\color{darkgray}\ttfamily,
 commentstyle=\it\color[RGB]{0,96,96}\ttfamily,
 stringstyle=\rmfamily\slshape\color[RGB]{128,0,0}\ttfamily,
 showstringspaces=false,
 language=c++,
 breaklines=true,
 postbreak=\mbox{\textcolor{red}{$\hookrightarrow$}\space}
}
\usepackage{listings}
\setCJKmainfont{Noto Sans CJK SC}
\usepackage{tocloft}
\renewcommand{\cftsecleader}{\cftdotfill{\cftdotsep}}
\setcounter{tocdepth}{2}
\usepackage{titling}
\renewcommand\maketitlehooka{\null\mbox{}\vfill}
\renewcommand\maketitlehookd{\vfill\null}

\title{\textbf{Templates for Competitive Programming}}
\author{\textbf{by kongroo}}
\begin{document}

\begin{titlingpage}
\maketitle
\end{titlingpage}

\clearpage
\tableofcontents
'''

code_temp = '''
\\begin{{lstlisting}}[language=c++]
{}
\\end{{lstlisting}}
'''


def remove_underscore(s):
    return s.replace('_', r'\_')


with open('result.tex' if len(sys.argv) < 2 else sys.argv[1], 'w') as fout:
    fout.write(header)
    sections = set()
    subsections = set()
    for f in sorted(glob.glob('**/*.cc', recursive=True)):
        lis = f.split('/')
        dep = len(lis)
        assert dep == 2 or dep == 3
        if lis[0] not in sections:
            fout.write('\\clearpage\n')
            sections.add(lis[0])
            fout.write('\\section{%s}\n' % remove_underscore(lis[0]))
            subsections = set()
        if lis[1] not in subsections:
            subsections.add(lis[1])
            fout.write('\\subsection{%s}\n' % remove_underscore(lis[1]))
        if dep == 3:
            print(f)
            fout.write('\\subsubsection{%s}\n' % remove_underscore(lis[-1]))
        fout.write(code_temp.format(open(f, 'r').read().strip()))
    fout.write(r'\end{document}')

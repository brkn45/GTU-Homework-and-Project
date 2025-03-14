
;; start interpreter function
(defun gppinterpreter (&optional (filename nil isFilename))
    (if isFilename
      (startInterpreter filename) 
      (interpreterShell)
  )
)
  
;; read line  from file convert
(defun startInterpreter (filename)
  (openfileWrite "parsedLisp.txt")
  (print "File has created.")
  (with-open-file (stream filename :direction :input)
    (loop for line1 = (read-line stream nil)
      while line1 do (if (> (length line1) 0)
                         (if (not (comment line1))
                           (tokenizeLine line1)))
      )
  )
)

;;read given string from shell
(defun interpreterShell ()
 (princ "Welcome to G++ shell, to exit enter empty string")
 (openfileWrite "parsed_lisp.txt")
 (format t "~%") (princ "> ")
  (let ((line ""))
    (loop for newLine = (read-line)
      while (> (length newLine) 0) do (if (not (comment newLine))
                                      (tokenizeLine newLine))
    )
   (print "File has created.")
  )
)

;;find paranthesis
(defun tokenizeLine (line)
  (let ((str) (tmpEnd -1))
    (loop for startIndex = 0 then (+ 1 endIndex)
      as endIndex = (position #\Space line :start startIndex)
      while endIndex do (progn (setf str (subseq line startIndex endIndex))
                                (if (> (length str) 0)
                                (DFA1 str))
                                (setf tmpEnd endIndex))
    )
    (if (= (length line) 1) (DFA1 line)
    (progn (setf str (subseq line (+ 1 tmpEnd) (length line)))
    (if (> (length str) 0)
      (DFA1 str))))
))


;;1 character tokens apply DFA analysis steps  
(defun DFA1(token)
   (if (= 1 (length token))
     (let ((chr (char token 0)))
     (cond ((operatorControll chr) t)
       ((digit chr) (writeFile "VALUE" nil))
       ((alpha-char-p chr) (writeFile "IDENTIFIER" nil))
       ((char= #\Newline chr) t)
       (t (writeFile chr t))))
   (DFA2 token))
)
;; DFA analaysis for long token
(defun DFA2 (token)
  (cond ((keywords token) t)
    ((comment token) t)
    ((is-value token) t)
    ((is-identifier token) t)
    ((operatorMult token) t)
    ((checkTabParanthesis token) t)
    (t (writeFile token t)))
)
;;find paranthesis
(defun checkParanthesis (token)
  (if (or (char= (char token 0) #\() (char= (char token 0) #\“)
          (char= (char token (- (length token) 1)) #\)) (char= (char token (- (length token) 1)) #\”))
    (progn (printParanthesisQuotes token) t) nil)
)
;;find tabs
(defun checkTabParanthesis (token)
  (if (char= (char token 0) #\Tab)
    (progn (removeTabs token) t) (checkParanthesis token))
)
;;remove tabs to make correct analysis
(defun removeTabs (token)
  (let ((counter 0))
    (loop for chr across token
      while (char= chr #\Tab) do (setf token (remove #\Tab token :count 1))
    )
    (DFA1 token)
  )
)
;;check operators
(defun operatorControll(chr)
  (cond ((char= chr #\+) (writeFile "OP_PLUS" nil))
    ((char= chr #\-) (writeFile "OP_MINUS" nil))
    ((char= chr #\/) (writeFile "OP_DIV" nil))
    ((char= chr #\() (writeFile "OP_OP" nil))
    ((char= chr #\)) (writeFile "OP_CP" nil))
    ((char= chr #\“) (writeFile "OP_OC" nil))
    ((char= chr #\”) (writeFile "OP_CC" nil))
    ((char= chr #\,) (writeFile "OP_COMMA" nil))
    ((char= chr #\*) (writeFile "OP_MULT" nil))
    (t nil))

)
;;check DBLMULT operator
(defun operatorMult (token)
  (if (= 2 (length token))
    (if (string= token "**") (writeFile "OP_DBLMULT" nil) nil) nil)
)
;;check comment
(defun comment (token)
(if (> (length token) 1)
  (if (search ";;" token :end2 2) (writeFile "COMMENT" nil) nil) nil)

)
;;check keywords
(defun keywords (token)
  (cond ((string= token "and") (writeFile "KW_AND" nil))
    ((string= token "or") (writeFile "KW_OR" nil))
    ((string= token "not") (writeFile "KW_NOT" nil))
    ((string= token "equal") (writeFile "KW_EQUAL" nil))
    ((string= token "less") (writeFile "KW_LESS" nil))
    ((string= token "nil") (writeFile "KW_NIL" nil))
    ((string= token "list") (writeFile "KW_LIST" nil))
    ((string= token "append") (writeFile "KW_APPEND" nil))
    ((string= token "concat") (writeFile "KW_CONCAT" nil))
    ((string= token "set") (writeFile "KW_SET" nil))
    ((string= token "deffun") (writeFile "KW_DEFFUN" nil))
    ((string= token "for") (writeFile "KW_FOR" nil))
    ((string= token "if") (writeFile "KW_IF" nil))
    ((string= token "exit") (writeFile "KW_EXIT" nil))
    ((string= token "load") (writeFile "KW_LOAD" nil))
    ((string= token "disp") (writeFile "KW_DISP" nil))
    ((string= token "true") (writeFile "KW_TRUE" nil))
    ((string= token "false") (writeFile "KW_FALSE" nil))
    (t nil))
)
;;check values
(defun is-value (token)
  (let ((counter 0))
    (loop for char across token
      while char do (if (not (digit char)) (setf counter (+ 1 counter)))
    )
    (if (= 0 counter) (if (char= (char token 0) #\0) nil (writeFile "VALUE" nil)) nil))
)
;;check digits
(defun digit (chr)
(cond ((char= chr #\0) t)
  ((char= chr #\1) t)
  ((char= chr #\2) t)
  ((char= chr #\3) t)
  ((char= chr #\4) t)
  ((char= chr #\5) t)
  ((char= chr #\6) t)
  ((char= chr #\7) t)
  ((char= chr #\8) t)
  ((char= chr #\9) t)
  (t nil))
)
;;check identifiers
(defun is-identifier (token)
  (if (digit (char token 0)) nil
    (if (every #'alphanumericp token) (writeFile "IDENTIFIER" nil) nil))
)


;;print and remove paranthesis to make correct analysis
(defun printParanthesisQuotes (token)
  (let ()
    (loop for chr across token
      while (or (char= chr #\() (char= chr #\“)) do (progn (operatorControll chr)
                                                           (setf token (remove chr token :count 1)))
    )
    (checkParanthesisAndQuotes token (endParanthesisQuotes token))
  )
)
;;get last paranthesis as list
(defun endParanthesisQuotes (token)
  (setf token (reverse token))
  (loop for chr across token
    while (or (char= chr #\)) (char= chr #\”)) collect chr
  )
)
;;print last paranthesis and apply DFA steps one more time.
(defun checkParanthesisAndQuotes (token mylist)
 (lastControl token (list-length mylist))
 (setf mylist (reverse mylist))
 (if (or (/= (list-length mylist) 1) (/= (length token) 1))
 (loop for parenth in mylist
   while parenth do (operatorControll parenth)
 ))
)
;;apply DFA steps one more time after paranthesis were removed.
(defun lastControl (token size)
  (let ((end (- (length token) size)))
       (if (= (length token) 1) (DFA1 token)
         (DFA1(subseq token 0 end)))
  )
)
;;open file in supersede mode to create.
(defun openfileWrite (filename)
  (with-open-file (stream filename  :direction :output
                                    :if-exists :supersede
                                    :if-does-not-exist :create))
)
;;open file in append mode to write.
(defun writeFile (lexicalResult is_error)
   (with-open-file (stream "parsed_lisp.txt" :direction :output
                                                :if-exists :append
                                                :if-does-not-exist :create)
         (if is_error
           (write-sequence (format nil "SYNTAX ERROR ~a cannot be tokenized.~%" (string lexicalResult)) stream)
           (write-sequence (format nil "~a~%" (string lexicalResult)) stream)))
)
;;check given command line arguments
(defun startTokenization ()
  (if *args*
    (gppinterpreter (first *args*))
    (gppinterpreter))
)
(startTokenization)
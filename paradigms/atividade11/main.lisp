(defun mdc (a b)
  (if (zerop b)
      a
      (mdc b (mod a b))))

(defun mmc (a b)
  (if (or (not (and (atom a) (atom b)))
          (not (> a 0))
          (not (> b 0)))
      nil
      (/ (* a b) (mdc a b))))

(print (mmc 0 3))    ; NIL
(print (mmc 2 -3))   ; NIL
(print (mmc 2 3))    ; 6
(print (mmc 12 45))  ; 180
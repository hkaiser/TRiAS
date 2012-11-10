search {
			select view default;
			select window as selected;
			<GeoSelectStatement>
			<WriteMerkmal>
		}
;									

GeoSelectStatement:
			  GeoSelectMethod ";"
			| GeoSelectMethod GeoSelect ";"
			| error
			;
			
GeoSelectMethod:
			  "RESELECT"		// ohne GeoSelect -> alle deselekt.
			| "ADDSELECT" 		// ohne GeoSelect -> alle selekt.			
			| "UNSELECT"		// ohne GeoSelect -> alle deselekt.
			| "NEGSELECT"		// immer ohne GeoSelct -> einfache Negation
			;

GeoSelect:    MerkmalSelectExpression
			| TriasObjektKlasse SelectOperator TriasObjektKlasse
			;
			
TriasObjektKlasse:                           
			  "&" INTEGER		// ohne Typangabe -> alle Typen
			| "&" ObjektKlassenTyp ":" INTEGER 			   
			;
			
ObjektKlassenTyp:
			  "P"
			| "F"
			| "L"
			| "T"
			;
			
SelectOperator:
			  "="			// bei String-Vergleich automat. rechts trimmen
			| ">"
			| "<"
			| "<>"
			| "CN"			// contain
			| "NC"			// not contain
			;                             
			      
TriasMerkmal: "$" INTEGER

Value:		  STRING
			| INTEGER
			| FLOAT
			// | DATE		// evtl. Datum
			;

MerkmalSelectExpression:
			  MSExpression 
			| MSExpression ConnectOperator MSExpression
			;

MSExpression: 
			  MerkmalValue GeoOperator Value
			| Value Geoperator MerkmalValue
			;
			
ConnectOperator:
			  "AND"
			| "OR"
			;
			
WriteMerkmal: "REPLACE" TriasMerkmal "WITH" MerkmalWriteExpression ";" // Typprüfung !
			| error
			;      

MerkmalWriteExpression:
			  MerkmalValue MerkmalOperator MerkmalValue
			| "(" MerkmalValue MerkmalOperator MerkmalValue ")" // Bearbeitungsreihenfolge !
			;
			
MerkmalOperator:
			  "+"
			| "-"
			| "*"
			| "/"
			| "^"
			;
						  			 			  			
			
			
			
			
			 						
									      
			      
			
			
			
						
						
						
			
			
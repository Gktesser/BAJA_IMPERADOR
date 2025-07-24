import cantools
import binascii

# Caminho correto com extensão .dbc
caminho_dbc = r"C:\Users\Pichau\OneDrive\Área de Trabalho\BAJA\PROGRAMA\dbc.dbc"

def testar_mensagem(db, id_msg, dados_hex):
    dados_bytes = binascii.unhexlify(dados_hex)
    msg = db.get_message_by_frame_id(id_msg)
    decoded = msg.decode(dados_bytes)
    print(f"\n📨 Mensagem: {msg.name} (ID: {id_msg})")
    for nome, valor in decoded.items():
        unidade = msg.get_signal_by_name(nome).unit or ""
        print(f"{nome}: {valor} {unidade}")

try:
    db = cantools.database.load_file(caminho_dbc)
    print("✅ DBC carregado com sucesso!")

    # Teste 1: PTECU_Dados_Motor (ID 32)
    testar_mensagem(db, 32, "D007E00100000000")
    # Teste 2: FECU_Inputs_Piloto (ID 257)
    testar_mensagem(db, 257, "6400320000000000")
    # Teste 3: MECU_Status_Seguranca (ID 273)
    testar_mensagem(db, 273, "0300000000000000")
    # Teste 4: PTECU_Alerts (ID 16)
    testar_mensagem(db, 16, "0100000000000000")
    # Teste 5: RECO_Status_Fusiveis (ID 1040)
    testar_mensagem(db, 1040, "0F00000000000000")

except Exception as e:
    print(f"❌ Erro ao carregar o DBC: {e}")
    